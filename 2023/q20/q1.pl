#!/usr/bin/perl -l
use strict;
use warnings;
my %scheme;
#		0	1	2		3		4
# name -> [ $type, $ninput, $offset, [ output,... ], [ outputidx,... ] ]
while(<>) {
    chomp;
    my $type = '';
    $type = $1 if s/^([%&])//;
    /\s*->\s*/ or die $_;
    my $src = $`; my $dst = $';
    my(@dst) = split /\s*,\s*/, $dst;
    $scheme{$src} ||= ['',0,0,[],[],$src];
    $scheme{$src}->[0] = $type;
    for my $dst (@dst) {
	$scheme{$dst} ||= ['',0,0,[],[],$dst];
	my $idx = $scheme{$dst}->[1]++;
	push @{$scheme{$src}->[3]}, $scheme{$dst};
	push @{$scheme{$src}->[4]}, $idx;
    }
}
my $button = $scheme{broadcaster} or die;
$button->[1] == 0 or die;
my $state = '';
{
    my $offset = 0;
    my $maxinput = 0;
    while(my($k,$v) = each %scheme) {
	$v->[1] = 1 if $v->[0] eq '%';
	my $bits = $v->[1];
	$bits = 8 if $bits > 1 && $bits < 8;
	$bits = 16 if $bits > 8 && $bits < 16;
	$bits = 32 if $bits > 16 && $bits < 32;
	#print STDERR "<< $k $v->[1] $offset $bits";
	$offset = ($offset + $bits - 1) & ~($bits - 1) if $bits;
	#print STDERR ">> $offset";
	$v->[2] = $offset;
	$offset += $bits;
	$maxinput = $v->[1] if $v->[1] > $maxinput;
    }
    $state = "\0" x ((($offset + 31)/32)*4);
    #vec($state, $offset - 1, 1) = 0;
    warn "$offset $maxinput";
}
use Data::Dumper;
#print STDERR Data::Dumper->Dump([\%scheme]);
#print STDERR unpack("b*", $state); 
my @cnt = (0, 0);
for my $i (1..1000) {
    my @q = [$button,0,0];
    while(@q) {
	my $u = shift @q;
	my($node,$ninput,$value) = @$u;
	++$cnt[$value];
	#print STDERR "$node->[5] $node->[0] $ninput $value";
	if($node->[0] eq '%') {
	    next if $value == 1;
	    $value = vec($state,$node->[2],1);
	    $value ^= 1;
	    vec($state,$node->[2],1) = $value;
	} elsif ($node->[0] eq '&') {
	    #print STDERR unpack("b*", $state);
	    vec($state,$node->[2] + $ninput, 1) = $value;
	    #print STDERR unpack("b*", $state);
	    my $bits = $node->[1];
	    $bits = 8 if $bits > 1 && $bits < 8;
	    $bits = 16 if $bits > 8 && $bits < 16;
	    $bits = 32 if $bits > 16 && $bits < 32;
	    my $val = 0 + vec($state,$node->[2]/$bits,$bits);
	    $value = $val == (1<<$node->[1]) - 1 ? 0 : 1;
	    #print STDERR ":: $node->[2] $bits = $val vs ", ((1<<$node->[1]) - 1);
	}
	for my $oidx (0..$#{$node->[3]}) {
	    my $dest = $node->[3]->[$oidx];
	    my $iidx = $node->[4]->[$oidx];
	    #print STDERR "->$value $dest->[5] $iidx";
	    push @q, [$dest,$iidx,$value];
	}
    }
    #print STDERR "=====";
}
print STDERR "@cnt";
print $cnt[0]*$cnt[1];
