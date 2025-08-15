#!/bin/bash

# Full file path as argument
fpath=$1

# Check if argument is provided
if [ -z "$fpath" ]; then
  echo "Usage: $0 <path-to-file>"
  exit 1
fi

# Extract filename without directory and extension
fname=$(basename "$fpath" .cpp)

# Build using make
make file="$fpath"

clear; clear;

# Run the output with a strict 1-second limit using Perl
perl -e '
  use POSIX ":sys_wait_h";

  my $pid = fork();
  die "fork failed: $!" unless defined $pid;

  if ($pid == 0) {
    exec @ARGV or exit 127;
  }

  $SIG{ALRM} = sub {
    kill "KILL", $pid;   # hard kill on timeout
    exit 124;            # align with GNU timeout convention
  };

  alarm 1;

  my $wp = waitpid($pid, 0);

  # Propagate child exit status
  my $code = $? >> 8;
  my $sig  = $? & 127;

  if ($sig) {
    exit 128 + $sig;     # standard bash convention for signal exits
  } else {
    exit $code;
  }
' ./build/"$fname"

status=$?

if [ $status -eq 124 ]; then
  echo "Error: Program exceeded 1 second(s) and was terminated"
  exit 124
elif [ $status -ne 0 ]; then
  exit $status
fi
