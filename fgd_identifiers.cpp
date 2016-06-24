#include "stdafx.h"
#include "fgd_identifiers.h"

using namespace std;

vector<string> wc_args =
{
	"HDR Full Compile -final -entE",
	"ente.exe",
	"$path\\$file.$ext",
	"\1\1",
	"$path\\$file.log $gamedir\\$file.log",
	"\1\1",
	"$path\\$file_new.$ext $gamedir\\$file.$ext",
	"$bsp_exe",
	"-game $gamedir $gamedir\\$file",
	"$vis_exe",
	"-game $gamedir $gamedir\\$file",
	"$light_exe",
	"-textureshadows -staticproppolys -staticproplighting -both -final -game $gamedir $gamedir\\$file",
	"\1\1",
	"$gamedir\\$file.bsp $path\\$file.bsp",
	"\1\1",
	"$gamedir\\$file.log $path\\$file.log",
	"\1\1",
	"$gamedir\\$file.prt $path\\$file.prt",
	"\2\1",
	"$gamedir\\$file.bsp",
	"\2\1",
	"$gamedir\\$file.prt",
	"\2\1",
	"$gamedir\\$file.log",
	"\2\1",
	"$gamedir\\$file.vmf",
	"\2\1",
	"$path\\$file_new.vmf"
};

vector<string> keyvalue_list = 
{ 
	"targetname",
	"parentname",
	"damagefilter",
	"target",
	"enemyfilter",
	"renamenpc",
	"templatename",
	"destinationgroup",
	"sourceentityname",
	"lightingorigin",
	"lightningstart",
	"lightningend",
	"ignoredentity",
	"targetentityname",
	"directionentityname",
	"lasertarget",
	"mainsoundscapename",
	"position0",
	"position1",
	"position2",
	"position3",
	"position4",
	"position5",
	"position6",
	"position7",
	"cpoint1",
	"cpoint2",
	"cpoint3",
	"cpoint4",
	"cpoint5",
	"cpoint6",
	"cpoint7",
	"cpoint8",
	"cpoint9",
	"cpoint10",
	"cpoint11",
	"cpoint12",
	"cpoint13",
	"cpoint14",
	"cpoint15",
	"cpoint16",
	"cpoint17",
	"cpoint18",
	"cpoint19",
	"cpoint20",
	"cpoint21",
	"cpoint22",
	"cpoint23",
	"cpoint24",
	"cpoint25",
	"cpoint26",
	"cpoint27",
	"cpoint28",
	"cpoint29",
	"cpoint30",
	"cpoint31",
	"cpoint32",
	"cpoint33",
	"cpoint34",
	"cpoint35",
	"cpoint36",
	"cpoint37",
	"cpoint38",
	"cpoint39",
	"cpoint40",
	"cpoint41",
	"cpoint42",
	"cpoint43",
	"cpoint44",
	"cpoint45",
	"cpoint46",
	"cpoint47",
	"cpoint48",
	"cpoint49",
	"cpoint50",
	"cpoint51",
	"cpoint52",
	"cpoint53",
	"cpoint54",
	"cpoint55",
	"cpoint56",
	"cpoint57",
	"cpoint58",
	"cpoint59",
	"cpoint60",
	"cpoint61",
	"cpoint62",
	"cpoint63",
	"nextkey",
	"slavename",
	"targetattachment",
	"moveto",
	"branch01",
	"branch02",
	"branch03",
	"branch04",
	"branch05",
	"branch06",
	"branch07",
	"branch08",
	"branch09",
	"branch10",
	"branch11",
	"branch12",
	"branch13",
	"branch14",
	"branch15",
	"branch16",
	"ignoredname01",
	"ignoredname02",
	"ignoredname03",
	"ignoredname04",
	"ignoredname05",
	"ignoredname06",
	"ignoredname07",
	"ignoredname08",
	"ignoredname09",
	"ignoredname10",
	"ignoredname11",
	"ignoredname12",
	"ignoredname13",
	"ignoredname14",
	"ignoredname15",
	"ignoredname16",
	"attach1",
	"attach2",
	"speakername",
	"source",
	"template01",
	"template02",
	"template03",
	"template04",
	"template05",
	"template06",
	"template07",
	"template08",
	"template09",
	"template10",
	"template11",
	"template12",
	"template13",
	"template14",
	"template15",
	"template16",
	"entitytemplate",
	"filtername",
	"filter01",
	"filter02",
	"filter03",
	"filter04",
	"filter05",
	"filter06",
	"filter07",
	"filter08",
	"filter09",
	"filter10",
	"lookatname",
	"damagetarget",
	"constraintsystem",
	"initialowner",
	"train",
	"toptrack",
	"bottomtrack",
	"newtarget",
	"altpath",
	"landmark",
	"soundscape",
	"measuretarget",
	"subject",
	"pointcamera",
	"measurereference",
	"targetreference",
	"animationtarget",
	"attachmentname",
	"emittername",
	"defaulttarget",
	"vehicle",
	"shovetargets",
	"snaptoent",
	"pathcornername",
	"followtarget",
	"followstrider",
	"levitategoal_bottom",
	"levitategoal_top",
	"launchpositionname",
	"landtarget",
	"rollerminetemplate",
	"npctemplate",
	"npctemplate2",
	"npctemplate3",
	"npctemplate4",
	"npctemplate5",
	"npctemplate6",
	"dustoff1",
	"dustoff2",
	"dustoff3",
	"dustoff4",
	"dustoff5",
	"dustoff6",
	"apcvehiclename",
	"contexttarget",
	"npctargetname",
	"spawngroup",
	"spawntarget",
	"fighttarget",
	"m_iszentity",
	"m_isznextscript",
	"goal",
	"waitpointname",
	"policetarget",
	"assaultpoint",
	"nextassaultpoint",
	"rallypoint",
	"safezone",
	"node_exit",
	"node01",
	"node02",
	"node03",
	"node04",
	"node05",
	"node06",
	"node07",
	"node08",
	"node09",
	"node10",
	"node11",
	"node12",
	"node13",
	"node14",
	"node15",
	"node16",
	"node17",
	"node18",
	"node19",
	"node20",
	"m_isznewtarget",
	"actor",
	"goalent",
	"control_volume",
	"npc_man_point",
	"laserentity",
	"airboat_gun_model",
	"barrel_volume",
	"specificresupply",
	"target1",
	"target2",
	"target3",
	"target4",
	"target5",
	"target6",
	"target7",
	"target8",
	"scene0",
	"scene1",
	"scene2",
	"scene3",
	"scene4",
	"scene5",
	"scene6",
	"scene7",
	"scene8",
	"scene9",
	"scene10",
	"scene11",
	"scene12",
	"scene13",
	"scene14",
	"scene15",
	"locationproxy",
	"missilehint",
	"firemissileat",
	"magnetname",
	"vortigaunt",
	"endtargetname",
	"glowentity1name",
	"glowentity2name",
	"glowentity3name",
	"glowentity4name",
	"glowentity5name",
	"glowentity6name",
	"glowentity7name",
	"glowentity8name",
	"glowentity9name",
	"glowentity10name",
	"extractzone",
	"extractcam",
	"spawn_target",
	"safe_zone_targetname",
	"target_name",
	"destination_group"
};

vector<string> input_list =
{
	"setparent",
	"forceinteractionwithnpc",
	"changepathcorner",
	"settrack",
	"flytospecifictrackviapath",
	"forcespawnatentityorigin",
	"detach",
	"setmeasuretarget",
	"target",
	"settargetreference",
	"setlocatortargetentity",
	"setanimationtarget",
	"setdefaulttargetentity",
	"settargetentity",
	"forcepickup",
	"sweeptarget",
	"sweeptargethighestpriority",
	"protecttarget",
	"setshovetarget",
	"setchargetarget",
	"throwgrenadeattarget",
	"setminiguntarget",
	"usesiegetargets",
	"extractbugbait",
	"chargetarget",
	"setcannontarget",
	"settargetpath",
	"hover",
	"setlandtarget",
	"dropbombattarget",
	"dropbombattargetalways",
	"inspecttargetphoto",
	"inspecttargetspotlight",
	"setfollowtarget",
	"setpickuptarget",
	"setfighttarget",
	"settargetposition",
	"settargetentityname",
	"settargetent",
	"dissolve",
	"objectivecompletetriggerextraction",
	"inputsettarget",
	"inputsetspawntarget",
	"inputspawn",
	"inputspawnignorevisibility",
	"setfogcontroller"
};
