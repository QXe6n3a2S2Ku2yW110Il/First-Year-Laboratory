#!/usr/bin/perl

@strings = ();
while (<>) {
    if ($_ =~ '<a ([\S]* )*href="(([a-zA-Z]+://)?(([\w\-]+\.)+[a-zA-Z]+)([\S]* )*[\S]*)"([\S]* )*[\S]*>') {
        push(@strings, $4);
    }
}

sub uniq {
    my %seen;
    grep !$seen{$_}++, @_;
}

@sorted = uniq(sort(@strings));
for (@sorted) {
    print $_, "\n";
}
