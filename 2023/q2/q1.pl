#!/usr/bin/perl -n
use warnings;
use strict;
chomp;
s/^Game (\d+): // or die;
my $id = $1;
our $sum;
$sum += $id;
my %base = (red => 12, green => 13, blue => 14);
OUTER:
for my $g (split /;\s*/, $_) {
    for my $c (split /,\s*/, $g) {
	my($cnt, $color) = split / /, $c;
	# print "$cnt $color $base{$color}\n";
	if ($cnt > $base{$color}) {
	    $sum -= $id;
	    last OUTER;
	}
    }
}    
END {
    print $sum
}
