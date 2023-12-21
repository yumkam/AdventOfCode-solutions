#!/usr/bin/perl -l
# converts AoC 2023/day20 input into graphviz .dot syntax
use strict;
use warnings;
print "digraph main {";
my %tr = ("%" => "box", "&" => "diamond");
while(<>) {
    chomp;
    my $type = '';
    $type = $1 if s/^([%&])//;
    /\s*->\s*/ or die $_;
    my $src = $`; my $dst = $';
    my(@dst) = split /\s*,\s*/, $dst;
    print qq{\t$src [shape="$tr{$type}"] ;} if $type;
    print "\t$src -> { @dst };"
}
print "}"
