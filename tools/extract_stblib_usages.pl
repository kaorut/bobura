#!/usr/bin/perl

# Standard library usage extractor.
# $Id$
# Copyright (C) 2007-2008 kaoru

use strict;

if (scalar(@ARGV) < 1)
{
	print 'Usage: ./extract_stdlib_usages.pl OPTIONS HEADERS_FILE'."\n";
	exit;
}

my(@includes, @included_headers);
my(%occurrences);
my(%headers) = read_stdlib_headers($ARGV[0]);
my(%used_headers);

for (my($line) = 1; <STDIN>; $line++)
{
	s/\r?\n$//g;
	
	if (/^\#[ ]*include \<([^\>]+)\>/)
	{
		my($filename) = $1;
		if ($filename !~ /\./ || $filename =~ /boost\//)
		{
			push(@includes, 'INC:    #include <'.$filename.'>');
			push(@included_headers, $filename);
		}
	}
	elsif (/^\/\/\#[ ]*include \<([^\>]+)\>/)
	{
		my($filename) = $1;
		if ($filename !~ /\./ || $filename =~ /boost\//)
		{
			push(@includes, 'INC: // #include <'.$filename.'>');
			push(@included_headers, $filename);
		}
	}
	elsif (
		/std::[a-zA-Z0-9_\:]*/ ||
		/assert/ ||
		/NULL/ ||
		/boost::[a-zA-Z0-9_\:]*/ ||
		/BOOST_[A-Z0-9_]*/
	)
	{
		my($code_line) = $_;
		while (
			$code_line =~ /(std::[a-zA-Z0-9_\:]*)/ ||
			$code_line =~ /(assert)/ ||
			$code_line =~ /(NULL)/ ||
			$code_line =~ /(boost::[a-zA-Z0-9_\:]*)/ ||
			$code_line =~ /(BOOST_[A-Z0-9_]*)/
		)
		{
			$occurrences{$1} .= $line.', ';
			$code_line =~ s/$1//;
		}
	}
}

my($value);
foreach $value (@includes)
{
	print $value."\n";
}

foreach $value (sort(keys(%occurrences)))
{
	my($header) = $headers{$value} eq '' ?
		'< UNKNOWN OPERATION >' : $headers{$value};
	printf("  %-48s %s\n", $value, $header);
	
	$used_headers{$header} = '*';
}

foreach $value (@included_headers)
{
	if ($used_headers{$value} eq '')
	{
		print 'WARNING: NOT USED: '.$value."\n";
	}
}

foreach $value (keys(%used_headers))
{
	if (scalar(grep(/^$value$/, @included_headers)) == 0)
	{
		print 'WARNING: NOT INCLUDED: '.$value."\n";
	}
}

sub read_stdlib_headers()
{
	my($filename) = @_;
	
	my(%result);
	open(FH, $filename) || die("Can't open $filename");
	while (<FH>)
	{
		s/\r?\n$//g;
		my($operation, $header) = split(/ +/);
		die "Duplicate operation: $operation" if $result{$operation} ne '';
		
		$result{$operation} = $header;
	}
	close(FH);
	
	return %result;
}
