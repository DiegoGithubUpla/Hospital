<?php
/*
	$conect = @mysql_connect("localhost","root","") or die("No se encontró el servidor");
	mysql_select_db("clase_php",$conect)or die("No se encontró la base de datos");
	*/

	/*------------------------------no ocupar mysqlconect----------------*/
	/*ocupar new mysqli , todas LAS CONECCTION CON PASWORD*/
	/*se ocupa int en los rut*/
	$server="localhost";
	$usu="root";
	$cont="";
	$base="clase_php";

/*select * from persona order by rut asc limit2*/


	$enlace = new mysqli($server,$usu, $cont,$base);

	if ($enlace->connect_error) {
    	die('Error de Conexión (' . $enlace->connect_errno . ') '
            . $enlace->connect_error);
	}
	//$PASWORD=password_hash("pas1",PASSWORD_DEFAULT);
	//echo($PASWORD);
	//echo "<br>";
	//$PASWORD=password_hash("pas1",PASSWORD_DEFAULT);
	//cho($PASWORD);
//$tam=mysql_query("INSERT into admin (`id`, `user`, `pw`) values('','usu1','$PASWORD');");
	//echo "hola";
//$enlace->query("INSERT into admin (`id`, `user`, `pw`) values('1','usu1','$PASWORD');");
?>