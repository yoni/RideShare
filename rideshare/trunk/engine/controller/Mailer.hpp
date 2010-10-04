#ifndef _MAILER_HPP
#define _MAILER_HPP

#include "DBAccess.hpp"
#include "Solution.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>

using optimizer::Solution;
using controller::dba::DBAccess;
using std::string;
using std::ofstream;
using std::stringstream;


class Mailer
{
public:
	Mailer(DBAccess::ptr dba, const Solution &solution)
		: mySolution( solution )
		, myDba( dba )
		, emails( myDba->getUserEmails(mySolution) )
		, perlMailerFile("mailer.pl")
	{} 

	string getUserEmails(string delimiter) const
	{
		stringstream ss;
		for(vector<string>::const_iterator it = emails.begin();
				it != emails.end();
				it++)
		{
			if (it != emails.begin())
				ss << delimiter; 
			ss << *it;
		}
		return ss.str();
	}

	void sendNotifications() const
	{
		string emails(getUserEmails("\\;"));
		dumpPerlMailer();
		setMailerPermissions();
		execMailer(emails);
		cleanup();
	}
	
private:
	Solution mySolution;
	DBAccess::ptr myDba;
	vector<string> emails;
	string perlMailerFile;

	void execMailer(string emailAddrs) const
	{
		stringstream ss;
		ss << "./" << perlMailerFile << " " << emailAddrs ;
		std::system(ss.str().c_str());
	}

	void cleanup() const
	{
		if ( remove(perlMailerFile.c_str() ) != 0)
		{
			perror("Error deleting perl mailer file");
		}
	}

	void setMailerPermissions() const
	{
		stringstream ss;
		ss << "chmod +x ";
		ss << perlMailerFile;
		int fd = open(perlMailerFile.c_str(), O_RDWR);
		fchmod(fd, S_IRWXU | S_IRWXG);
		close(fd);
	}

	void dumpPerlMailer() const
	{
		ofstream oFile;
		oFile.open(perlMailerFile.c_str(), std::ios::out);
		oFile << "#!/usr/bin/perl\n";
		oFile << "unless ($#ARGV == 0)\n";
		oFile << "{\n";
		oFile << "	print \"Correct usage: ./mailer.pl destination\\@gmail.com\\n\";\n";
		oFile << "	warn \"Could not send notification email\";\n";
		oFile << "} \n";
		oFile << "else\n";
		oFile << "{\n";
		oFile << "@emails = split(/;/, $ARGV[0]);\n";
		oFile << "foreach(@emails) { \n";
		oFile << "\t$emailAddr = $_;\n";
		oFile << "\tunless(open (MAIL, \"|/usr/sbin/sendmail $emailAddr\")) {\n";
		oFile << "\tprint \"error.\\n\";\n";
		oFile << "\twarn \"Error starting sendmail: $!\";\n";
		oFile << "\t}\n";
		oFile << "\telse{\n";
		oFile << "\tprint MAIL \"From: Rideshare Notification\\n\";\n";
		oFile << "\tprint MAIL \"Subject: You have a new Rideshare!\\n\\n\";\n";
		oFile << "\tprint MAIL \"You have been matched in a Rideshare.  Login to your account \";\n";
		oFile << "\tprint MAIL \"below to see your new match!\\n\\n\";\n";
		oFile << "\tprint MAIL \"Rideshare Login - http://rideshare.ece.utexas.edu\\n\\n\";\n";
		oFile << "\tprint MAIL \"Thanks,\\nThe Rideshare Team\";\n";
		oFile << "\tclose(MAIL) || warn \"Error closing mail: $!\";\n";
		oFile << "\tprint \"Mail sent to $emailAddr\\n\";\n";
		oFile << "}\n}\n}";
		oFile.close();
	}

};

#endif // #ifndef _MAILER_HPP
