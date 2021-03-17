#!/usr/bin/perl

@strings = ();

$prev_is_empty = 0;
while (<>) {
    $curr_is_empty = ($_ =~ /^\s*$/);
    if (!($prev_is_empty && $curr_is_empty)) {
        push(@strings, $_);
    }

    $prev_is_empty = $curr_is_empty;
}

# print "Reading is ended\n";

# for (@strings) {
#     print $_, "\n";
# }

$start = -1;
$end = -1;
for (my $i = 0; $i <= $#strings; ++$i) {
    if ($strings[$i] !~ /^\s*$/) {
        if ($start == -1) {
            $start = $i;
        }
        $end = $i;
    }
}

# print $start, " ", $end, "\n";

for (my $i = $start; $i <= $end; ++$i) {
    # print "before ", length($strings[$i]), " ", $strings[$i], "\n";
    $strings[$i] =~ s/^\s+(.*?)$/\1/;
    # print "middle ", length($strings[$i]), " ", $strings[$i], "\n";
    $strings[$i] =~ s/^(.*?)\s+$/\1/;
    # print "after ", length($strings[$i]), " ", $strings[$i], "\n";
    $strings[$i] =~ s/(\s){2,}/\1/g;
    print $strings[$i], "\n";
}