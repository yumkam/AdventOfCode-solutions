#!/usr/bin/perl -aln
use warnings;
use strict;
our $res;
my @aoa = [@F];
for (;;) {
    my $anynz = 0;
    my @a;
    my $last = $aoa[$#aoa];
    push @aoa, [];
    my $cur = $aoa[$#aoa];
    for my $i (1..$#{$last}) {
	my $diff = $last->[$i] - $last->[$i-1];
	$anynz ||= $diff;
	push @$cur, $diff
    }
    last unless $anynz;
}
for (my $i = scalar @aoa; $i-- > 1; ) {
    push @{$aoa[$i - 1]}, $aoa[$i - 1]->[$#{$aoa[$i - 1]}] + $aoa[$i]->[$#{$aoa[$i]}];
}
$res +=  $aoa[0]->[$#{$aoa[0]}];
END {
    print $res
}
