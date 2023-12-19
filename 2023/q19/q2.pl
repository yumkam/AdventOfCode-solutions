#!/usr/bin/perl -l
use strict;
use warnings;
my %rules;
my(@tr) = (undef) x 256;
$tr[ord('x')] = 0;
$tr[ord('m')] = 1;
$tr[ord('a')] = 2;
$tr[ord('s')] = 3;
while(<>) {
    chomp;
    last unless length $_;
    s/^([a-z]+)// or die $_;
    my $name = $1;
    s/^\{// or die $_;
    s/\}$// or die $_;
    my @F = split /,/;
    my $def = pop @F;
    my @r;
    for my $rule (@F) {
	$rule =~ /^([xmas])([<>])(\d+):([AR]|[a-z]+)$/ or die $rule;
	push @r, [$tr[ord($1)], $2, $3,$4];
    }
    $rules{$name} = [\@r,$def];
}
my $res = 0;
sub min($$) { $_[0] < $_[1] ? $_[0] : $_[1] }
sub max($$) { $_[0] > $_[1] ? $_[0] : $_[1] }
sub nest(&\$\$$$) {
    my($call,$minref,$maxref,$op,$val) = @_;
    #print STDERR "$$minref $$maxref $op $val";
    if ($op eq '>') {
	my $save = $$minref;
	$$minref = $val + 1;
	&$call;
	$$minref = $save;
	$$maxref = $val;
    } else {
	my $save = $$maxref;
	$$maxref = $val - 1;
	&$call;
	$$maxref = $save;
	$$minref = $val;
    }
}
sub dfs($$$$$$$$$);
sub dfs($$$$$$$$$) {
    my ($name, $xmin, $xmax, $mmin, $mmax, $amin, $amax, $smin, $smax) = @_;
    #print STDERR "$name, $xmin, $xmax, $mmin, $mmax, $amin, $amax, $smin, $smax";
    return if $xmin > $xmax or $mmin > $mmax or $amin > $amax or $smin > $smax;
    if (length($name) == 1) {
	return if $name eq 'R';
	$res += ($xmax - $xmin + 1)*($mmax - $mmin + 1)*($amax - $amin + 1)*($smax - $smin + 1);
	return;
    }
    my $rule = $rules{$name};
    for my $x (@{$rule->[0]}) {
	my($id,$op,$val,$dest) = @$x;
	if ($id == 0) { nest { dfs($dest,$xmin,$xmax,$mmin,$mmax,$amin,$amax,$smin,$smax) } $xmin, $xmax, $op, $val; }
	elsif ($id == 1) { nest { dfs($dest,$xmin,$xmax,$mmin,$mmax,$amin,$amax,$smin,$smax) } $mmin, $mmax, $op, $val; }
	elsif ($id == 2) { nest { dfs($dest,$xmin,$xmax,$mmin,$mmax,$amin,$amax,$smin,$smax) } $amin, $amax, $op, $val; }
	elsif ($id == 3) { nest { dfs($dest,$xmin,$xmax,$mmin,$mmax,$amin,$amax,$smin,$smax) } $smin, $smax, $op, $val; }
    }
    dfs($rule->[1],$xmin,$xmax,$mmin,$mmax,$amin,$amax,$smin,$smax);
}
dfs('in',1,4000,1,4000,1,4000,1,4000);
print $res;
