#!/usr/bin/perl -n
use warnings;
use strict;
our $sum;
chomp;
s/^Game (\d+): // or die;
my $id = $1;
my %stat;
OUTER:
for my $g (split /;\s*/, $_) {
    for my $c (split /,\s*/, $g) {
	my($cnt, $color) = split / /, $c;
	$stat{$color} = $cnt if $cnt > ($stat{$color} || 0);
    }
}
my $p = 1;
for my $color (qw/red green blue/) {
    $p *= $stat{$color};
}
warn "$id, $p\n" unless $p;
#print STDERR "$id $p\n";
$sum += $p;
END {
    print $sum
}
