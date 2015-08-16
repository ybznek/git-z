#!/usr/bin/env php
<?php
exec("git log --help",$cmds);
$classPath="./Git-z/GitLogFormat.hpp";
function cb($m){
	return strtoupper($m[1]);
}
$cnt=[];
$items=[];
foreach ($cmds as $cmd) {
	if (preg_match_all('|^\s*·\s*%([@%\w]+):\s*([^\\.\\("%]*)|',$cmd,$m,PREG_SET_ORDER)) {		
		$msg = trim($m[0][2]);
		$msg = str_replace(array(',','-'),'',$msg);
		$msg = preg_replace_callback("| (\w)|","cb",$msg);
		
		if (isset($cnt[$msg])){
			$cnt[$msg]++;
			$msg.=$cnt[$msg];
		}else {
			$cnt[$msg] = 1;
		}
		
		$items[]=["str"=>$m[0][1],"msg"=>$msg];
	}
}

$output ="//Generated from ".pathinfo(__FILE__,PATHINFO_FILENAME)." ".date(DATE_RFC2822)."\n";
$output .= <<<HEAD
#ifndef GITLOGFORMAT_HPP
#define GITLOGFORMAT_HPP

namespace gitz{
class GitLogFormat
{
       public:

HEAD;

foreach ($items as $item) {
$output.=str_pad("\t\tstatic const char* $item[msg]()",70," ")."{ return \"%$item[str]\"; }\n";
}


$output.= <<<FOOT

        private: inline GitLogFormat() {} // make class static
};

}
#endif // GITLOGFORMAT_HPP
FOOT;
file_put_contents($classPath,$output);
//print_r($items);
