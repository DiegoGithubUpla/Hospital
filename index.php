<?php
  session_start();
  include 'serv.php';
  if(isset($_SESSION['user'])){
  echo '<script> window.location="panel.php"; </script>';
  }
?>
<!DOCTYPE html>
<html lang="en">

  <head>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>HOSLA</title>

    <!-- Bootstrap core CSS -->
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="css/blog-post.css" rel="stylesheet">

  </head>

  <body>
      <!--moddal login-->
      <div class="modal fade" id="myModal" role="dialog">
    <div class="modal-dialog modal-sm">
      <div class="modal-content">
        <div class="modal-header">
          <!--button type="button" class="close" data-dismiss="modal">&times;</button-->
          <h4 class="modal-title">Login Usuario</h4>
        </div>
        <div class="modal-body">

  <form class="form-horizontal"  method="post" action="validar.php">
        <div class="form-group">
          <label class="control-label col-sm-2" for="usuario">USUARIO:</label>
          <div class="col-sm-12">
            <input type="text" class="form-control" id="usuario" placeholder="Ingresa usuario" name="user">
          </div>
        </div>
        <div class="form-group">
          <label class="control-label col-sm-2" for="pwd">CONTRASEÑA:</label>
          <div class="col-sm-12">          
            <input type="password" class="form-control" id="pwd" placeholder="Ingresa clave" name="pw">
          </div>
        </div>
        
        <div class="form-group">        
          <div class="col-sm-offset-2 col-sm-10">
            <button type="submit" class="btn btn-default" name="login">Entrar</button>
          </div>
        </div>
  </form>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">Cerrar</button>
        </div>
      </div>
    </div>
  </div>

    <!-- Navigation -->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top">
      <div class="container">
        <a class="navbar-brand" href="#">HOSLA</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarResponsive" 
        aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarResponsive">
          <ul class="navbar-nav ml-auto">
            <li class="nav-item">
              <a class="nav-link" href="#" data-toggle="modal" data-target="#myModal">Login</a>
            </li>
          </ul>
        </div>
      </div>
    </nav>

    
    <div class="container">

      <div class="row">

       

        <div class="col-md-2">

         

          
        </div>
                      <div class="col-lg-8">

                       
                          <h3 class="mt-4">SISTEMA DE MINIMIZACIÓN DE TIEMPO DE TRASLADO Y MONITOREO</h3>

                        
                          <img class="img-fluid rounded" src="foto1.jpg" alt="">

                          <hr>

                          
                              <p class="lead">Este sistema permite que los funcionarios a cargo del transporte de los pacientes
                               pendientes de intervención quirúrgica puedan minimizar el tiempo de traslado, impidiendo el retardo
                                causado por la manipulación constante de las puertas que dan acceso al pabellón, como también de 
                                la puerta principal y la rápida autentificación para el ingreso al sector de operaciones.  
                                Además de entregar información estratégica y estadística sobre las camillas
                                </p>


                              <hr>

                              
                        

                      </div>

        
        <div class="col-md-2">

          

          
        </div>

      </div>
      

    </div>
    

    <!-- Footer -->
    <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; Your Website 2017</p>
      </div>
      <!-- /.container -->
    </footer>

    <!-- Bootstrap core JavaScript -->
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

  </body>

</html>