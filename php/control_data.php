<?php
       $servername = "localhost";
       $username = "root";
       $password = "";
       $dbname = "test";
       $conn = new mysqli($servername, $username, $password, $dbname) or die("unable to connect to database");



       $name="";
       $cognome="";
       $sesso="";
      if(isset($_POST['submit']))
          {
              $name = $_POST['nome'];
              $cognome = $_POST['cognome'];
              $name = $_POST['radio'];
              $conn->query("insert into dati(nome, cognome, sesso) values('$name', '$cognome', '$sesso')");
          if(!$conn)
          { echo mysqli_error(); }
      else
      {
          echo "Successfully Inserted <br />";

      }
           }
?>
