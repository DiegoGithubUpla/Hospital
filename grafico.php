<html>
  <head>
  
  <link href="vendor/jquery/jquery.min.js" rel="stylesheet">
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="vendor/bootstrap/js/bootstrap.min.js" rel="stylesheet">
    <script type="text/javascript" src="js/loader.js"></script>
    <script type="text/javascript">
      //grafico de barras
      google.charts.load('current', {'packages':['bar']});
      google.charts.setOnLoadCallback(drawChart);

      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['Dias', 'Cantidad']
          <?php
          
            include 'serv.php';
            $consulta='select count(idCam) as cant,fecha from camilla GROUP by fecha';
              $result = $enlace->query($consulta);
              
              if ($result->num_rows > 0) {
                  while($row = $result->fetch_assoc()) {
                    echo ",['".$row["fecha"]."',".$row["cant"]."]";
                  }  
               
              }
              $enlace->close();
              
          ?>
        ]);

        var options = {
          chart: {
            title: 'Cantidad de procedimientos por dia',
            subtitle: 'Cantidad/Dia',
          }
        };

        var chart = new google.charts.Bar(document.getElementById('columnchart_material'));

        chart.draw(data, google.charts.Bar.convertOptions(options));
      }
    </script>

    <script type="text/javascript">
    //grafico de torta
      google.charts.load('current', {'packages':['corechart']});
      google.charts.setOnLoadCallback(drawChart);

      function drawChart() {

        var data = google.visualization.arrayToDataTable([
          ['Procedimientos', 'Cantidad']
          <?php
          
            include 'serv.php';
            $consulta="SELECT (SELECT COUNT(idCam) from camilla) as total,(SELECT COUNT(idCam) from camilla WHERE tac=1) AS subtotal FROM camilla LIMIT 1";
              $result = $enlace->query($consulta);
              
              if ($result->num_rows > 0) {
                $row = $result->fetch_assoc();
                if($row["subtotal"]%2==0){
                  echo ",['"."Total de procedimientos"."',".$row["total"]."]";
                  echo ",['"."Procedimientos Completados"."',".$row["subtotal"]."]";
                }else{
                  echo ",['"."Total de procedimientos"."',".$row["total"]."]";
                  echo ",['"."Procedimientos Completados"."',".($row["subtotal"]-1)."]";
                }  
              }
              $enlace->close();
              
          ?>
          /*
          ['Work',     11],
          ['Eat',      2],
          ['Commute',  2],
          ['Watch TV', 2],
          ['Sleep',    7]*/
        ]);

        var options = {
          title: 'Cantidad de procedimientos'
        };

        var chart = new google.visualization.PieChart(document.getElementById('piechart'));

        chart.draw(data, options);
      }
    </script>

    <script type="text/javascript">
      google.charts.load('current', {'packages':['bar']});
      google.charts.setOnLoadCallback(drawChart);

      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['Dia', 'Procedimientos/Hora'/*, 'Expenses', 'Profit'*/]
          <?php
          
            include 'serv.php';
            $consulta='SELECT max(hora) as maxHora,min(hora) as minHora,COUNT(idCam) as numero,fecha FROM camilla GROUP by fecha';
              $result = $enlace->query($consulta);
              $tabla="";
              $mayor=0;
              $menor=100000000;
              if ($result->num_rows > 0) {
                  while($row = $result->fetch_assoc()) {
                    //echo ",['".$row["fecha"]."',".$row["cant"]."]";
                    $terMax=$row["maxHora"];
                    $terMin=$row["minHora"];
                    $cont=1;
                    $segMin=0;
                    $segMax=0;
                    $horaFinal1='';
                    $horaFinal2='';
                    while($cont<4){
                      if($cont==1){

                        $segMax=$segMax+$terMax%100;
                        $segMin=$segMin+$terMin%100;
                        $horaFinal1=((string)$terMax%100);
                        $horaFinal2=((string)$terMin%100);
                      }
                      if($cont==2){

                          $segMin=$segMin+($terMin%100)*60;
                          $segMax=$segMax+($terMax%100)*60;
                          $horaFinal1=((string)$terMax%100).':'.$horaFinal1;
                          $horaFinal2=((string)$terMin%100).':'.$horaFinal2;
                      }
                      if($cont==3){
                        
                        
                          $segMin=$segMin+($terMin%100)*3600;
                          $segMax=$segMax+($terMax%100)*3600;
                          $horaFinal1=((string)$terMax%100).':'.$horaFinal1;
                          $horaFinal2=((string)$terMin%100).':'.$horaFinal2;
                      }
                        $terMin=floor($terMin/100);
                        $terMax=floor($terMax/100);
                        $cont++;
                    }

                    $resultadoSegundos=$segMax-$segMin;
                    
                    if($resultadoSegundos!=0){
                      $velocidad=(($row["numero"]/$resultadoSegundos))/0.000277778;
                    }else{
                      $velocidad=0;
                    }
                    echo ",['".$row["fecha"]."',".$velocidad."]";

                    $tabla=$tabla."<tr>
                              <td>".$row["fecha"]."</td>
                              <td>".$row["numero"]."</td>
                              <td>".$horaFinal2." hrs</td>
                              <td>".$horaFinal1." hrs</td>
                              <td>".$resultadoSegundos." seg</td>
                            </tr>";
                      //calcular el dia más productivo
                       if($mayor<$velocidad){
                          $mayor=$velocidad;
                          $diaMasProductivo=$row["fecha"];
                       }
                       if($menor>$velocidad){
                          $menor=$velocidad;
                          $diaMenosProductivo=$row["fecha"];
                       }

                  }  
               
              }
              $enlace->close();
              
          ?>
          /*
          ['2014', 1000, 400, 200],
          ['2015', 1170, 460, 250],
          ['2016', 660, 1120, 300],
          ['2017', 1030, 540, 350]*/
        ]);

        var options = {
          chart: {
            title: 'Velocidad del proceder/hora',
            subtitle: 'Evaluación de rendimiento',
          }
        };

        var chart = new google.charts.Bar(document.getElementById('columnchart_material2'));

        chart.draw(data, google.charts.Bar.convertOptions(options));
      }
    </script>
  </head>
  <body>
    <div id="columnchart_material" style="width: 800px; height: 500px;"></div>
    <div id="piechart" style="width: 900px; height: 500px;"></div>
    <div id="columnchart_material2" style="width: 800px; height: 500px;"></div>
    <div class="container">
  <h2>Estadistica</h2>
              
  <table class="table table-condensed">
    <thead>
      <tr>
        <th>Fecha</th>
        <th>Cantidad</th>
        <th>Inicio</th>
        <th>Final</th>
        <th>Tiempo</th>
      </tr>
    </thead>
    <tbody>
    <?php
        echo $tabla;
      ?>
    </tbody>
  </table>
</div>
<blockquote>
  <p>Para medir la productividad considera la cantidad de acciones realizadas y el tiempo</p>
</blockquote>
  <blockquote>
  <p><?php echo "El dia más productivo fue: ".$diaMasProductivo;?></p>
</blockquote> 
<blockquote>
  <p><?php echo "El dia menos productivo fue: ".$diaMenosProductivo; ?></p>
</blockquote>

<a href="archivosPdf/examples/example_065.php?tabla=<?php echo $tabla; ?>">Descargar</a>

  
  </body>
</html>