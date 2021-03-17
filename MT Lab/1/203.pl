#!/usr/bin/perl

while (<>) {
    s/\ba+\b/argh/i;
    print;
}