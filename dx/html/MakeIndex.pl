#!/usr/bin/perl

use strict;
use warnings;

use HTML::TreeBuilder;

my @commonList = <DATA>;
chomp @commonList;

print "profiles = new Array(\n";

my $i = 0;
my @files = @ARGV;

foreach my $fileName (@files) {
    $fileName =~ s/^\.\///;
    my %uniqueWords;
    my $tree = HTML::TreeBuilder->new();
    $tree->parse_file($fileName);
    my $title = $tree->find_by_tag_name('title');
    my @titlestr = $title->content_list();
    $titlestr[0] =~ s/,/ /g;
    my @text = $tree->as_text();
    foreach my $sym (@text) {
	$sym =~ s/[^a-zA-Z0-9\-_]/ /g;
	$sym =~ s/--/ /g;
	$sym =~ s/([b-df-hj-np-rtv-z])s($|[\s\n])/$1 /g; # eliminate plurals
	my @symar = split(" ", $sym);
	foreach my $sym2 (@symar) {
	    if(length($sym2) > 3) {
		$sym2 = lc($sym2);
		# don't add too common words like contents
		my $test = 1;
		foreach my $cw (@commonList) {
		    if($sym2 eq $cw) {
			$test = 0;
			last;
		    }
		}
		if($test) {
		    $uniqueWords{$sym2}++;
		}
	    }
	}	
    }
    print "\t\"" . $fileName . "|";
    print $titlestr[0] . "|";
    my @sortwords = sort { $uniqueWords{$b} <=> $uniqueWords{$a} } keys %uniqueWords;
    foreach my $word (@sortwords) {
	print " $word $uniqueWords{$word}";
    }
    print "\"";
    if($i != $#files) {
	print ",\n";
    }
    $tree->delete;
    $i++;
}

print "\n);\n";

__END__
about
after
also
been
both
contents
customer
does
each
either
from
have
here
hereof
home
however
into
legal
like
make
many
most
next
only
same
shall
should
since
some
such
sure
table
that
their
then
thereof
these
this
those
used
user
using
value
well
were
when
will
with
within
without
your
deal
item
whose
what
onto
html
know
thus
over
than
away
they
whether
much
thing
another
more
itself
even
want
would
upon



