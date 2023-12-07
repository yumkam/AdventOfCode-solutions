#!/usr/bin/perl -aln
use warnings;
use strict;
our @arr;
die unless length($F[0]) == 5;
(my $x = $F[0]) =~ y/AKQJT98765432/abcdefghijklm/;
my %m;
for my $c (split //, $x) { $m{$c}++ }
my @m = sort { $b <=> $a } values %m;
my $c = $m[0] == 5 ? 'A' : # five of kind
	$m[0] == 4 ? 'B' : # four of kind
	$m[0] == 3 && $m[1] == 2 ? 'C' : # full house
	$m[0] == 3 ? 'D' : # three of kind
	$m[0] == 2 && $m[1] == 2 ? 'E' : # two pair
	$m[0] == 2 ? 'F' : # one pair
	'G'; # high card
# print STDERR "$F[0] @m $c $x";
push @arr, ["$c$x",$F[1],$F[0]];
END {
    my $rank = 0;
    my $res = 0;
    for my $x (sort { $b->[0] cmp $a->[0] } @arr) {
	$res += $x->[1] * (++$rank);
	# print STDERR "$x->[2] $rank"
    }
    print $res
}
