//Generated from generateFormatClass Sat, 15 Aug 2015 23:45:18 +0000
#ifndef GITLOGFORMAT_HPP
#define GITLOGFORMAT_HPP

namespace gitz{
class GitLogFormat
{
       public:
		static const char* commitHash()                                     { return "%H"; }
		static const char* abbreviatedCommitHash()                          { return "%h"; }
		static const char* treeHash()                                       { return "%T"; }
		static const char* abbreviatedTreeHash()                            { return "%t"; }
		static const char* parentHashes()                                   { return "%P"; }
		static const char* abbreviatedParentHashes()                        { return "%p"; }
		static const char* authorName()                                     { return "%an"; }
		static const char* authorName2()                                    { return "%aN"; }
		static const char* authorEmail()                                    { return "%ae"; }
		static const char* authorEmail2()                                   { return "%aE"; }
		static const char* authorDate()                                     { return "%ad"; }
		static const char* authorDateRFC2822Style()                         { return "%aD"; }
		static const char* authorDateRelative()                             { return "%ar"; }
		static const char* authorDateUNIXTimestamp()                        { return "%at"; }
		static const char* authorDateISO8601likeFormat()                    { return "%ai"; }
		static const char* authorDateStrictISO8601Format()                  { return "%aI"; }
		static const char* committerName()                                  { return "%cn"; }
		static const char* committerName2()                                 { return "%cN"; }
		static const char* committerEmail()                                 { return "%ce"; }
		static const char* committerEmail2()                                { return "%cE"; }
		static const char* committerDate()                                  { return "%cd"; }
		static const char* committerDateRFC2822Style()                      { return "%cD"; }
		static const char* committerDateRelative()                          { return "%cr"; }
		static const char* committerDateUNIXTimestamp()                     { return "%ct"; }
		static const char* committerDateISO8601likeFormat()                 { return "%ci"; }
		static const char* committerDateStrictISO8601Format()               { return "%cI"; }
		static const char* refNamesLikeTheDecorateOptionOfGitlog()          { return "%d"; }
		static const char* refNamesWithoutThe()                             { return "%D"; }
		static const char* encoding()                                       { return "%e"; }
		static const char* subject()                                        { return "%s"; }
		static const char* sanitizedSubjectLineSuitableForAFilename()       { return "%f"; }
		static const char* body()                                           { return "%b"; }
		static const char* rawBody()                                        { return "%B"; }
		static const char* commitNotes()                                    { return "%N"; }
		static const char* rawVerificationMessageFromGPGForASignedCommit()  { return "%GG"; }
		static const char* showTheNameOfTheSignerForASignedCommit()         { return "%GS"; }
		static const char* showTheKeyUsedToSignASignedCommit()              { return "%GK"; }
		static const char* reflogSelectorE()                                { return "%gD"; }
		static const char* shortenedReflogSelectorE()                       { return "%gd"; }
		static const char* reflogIdentityName()                             { return "%gn"; }
		static const char* reflogIdentityName2()                            { return "%gN"; }
		static const char* reflogIdentityEmail()                            { return "%ge"; }
		static const char* reflogIdentityEmail2()                           { return "%gE"; }
		static const char* reflogSubject()                                  { return "%gs"; }
		static const char* switchColorToRed()                               { return "%Cred"; }
		static const char* switchColorToGreen()                             { return "%Cgreen"; }
		static const char* switchColorToBlue()                              { return "%Cblue"; }
		static const char* resetColor()                                     { return "%Creset"; }
		static const char* leftRightOrBoundaryMark()                        { return "%m"; }
		static const char* newline()                                        { return "%n"; }
		static const char* aRaw()                                           { return "%%"; }
		static const char* printAByteFromAHexCode()                         { return "%x00"; }

        private: inline GitLogFormat() {} // make class static
};

}
#endif // GITLOGFORMAT_HPP