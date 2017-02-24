<?php
global $user;
$username= $user ->name;
$param12=array('UserName'=>"$username");
 $client12= new soapclient('http://etypeservices.com/service_GetPublicationIDByUserName.asmx?WSDL');
    $response12=$client12->GetPublicationID($param12);
    
       
     if($response12->GetPublicationIDResult== -9)
    {
    
    }  
    else if($response12->GetPublicationIDResult== 3211)
    {
			header ("location:http://etypeservices.com/ReadTheEdition.aspx?Username=$username&Pub=3211&PType=Beaches3211LDREtypXX");
	}
	else if($response12->GetPublicationIDResult== 3212)
	{
		header ("location:http://etypeservices.com/ReadTheEdition.aspx?Username=$username&Pub=3212&PType=PVedra3212VedraXeTy0");
	}
?>
