#!/usr/bin/perl

while (<>) {
    print if /(^[^\s]*$)|(^[^\s]+([^\s]*\s*)*[^\s]+$)/
}