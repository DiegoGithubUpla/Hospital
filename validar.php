<?php
	session_start(); 
?>
<!DOCTYPE html>
<html>
<head>
<head>
	<title>Validando...</title>
	<meta charset="utf-8">
</head>
<body>
		<?php
			include 'serv.php';
			if(isset($_POST['login'])){
				$usuario = $_POST['user'];
				$pw = $_POST['pw'];
				$largo = $enlace->query("SELECT * FROM admin WHERE user='$usuario'");
				if ($largo->num_rows > 0) {
					$row = $largo->fetch_assoc();
						if(password_verify($pw,$row['pw'])){
							echo 'contraseña correcta';
						}else{
							echo 'contraseña no correcta';
						}
						$_SESSION["user"] = $row['user']; 
					  	echo 'Iniciando sesión para '.$_SESSION['user'].' <p>';
						echo '<script> window.location="panel.php"; </script>';
				
				}else{
					echo '<script> alert("Usuario o contraseña incorrectos.");</script>';
					echo '<script> window.location="index.php"; </script>';
				}
			}
		?>	
</body>
</html>