<?php
if(isset($_POST['submit']))
{
	$publication=$_POST['publication'];
	if($publication==3211)
	{
		header ("location:http://www.etypeservices.com/Beaches%20LeaderID585/");
	}
	if($publication==3212)
	{
		header ("location:http://www.etypeservices.com/Ponte%20Vedra%20LeaderID586/");
	}
}

?>

<!--<form name="form1" method="POST" action="http://www.stmarynow.com/node/19014" enctype="multipart/form-data">
      -->
	  <form name="form1" method="POST" action="" enctype="multipart/form-data">
	  
	  <fieldset>
               
                
            <div>
<h3 style="background:gray;line-height: 2.0em;font-size: 16px;"><center>Select Publication</center></h3>
<br/>
<hr>
               <input type="radio" name="publication" value="3211" required>Beaches Leader<br>
         <input type="radio" name="publication" value="3212">Ponte Vedra Leader<br>
            </div>

            
 
 <br/>
            
 
        
 
            
 
 
            
            </fieldset>
                
        <input type="submit" name="submit" value="Submit!" style="background-color: gainsboro;border-radius: 4px;width: 93px;height: 28px;border: 1px solid #CCC;text-decoration: none;color: #000;text-shadow: white 0 1px 1px;padding: 2px;">
                      
        </form>