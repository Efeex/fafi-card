<?php
       $servername = "localhost";
       $username = "root";
       $password = "";
       $dbname = "test";
       $conn = new mysqli($servername, $username, $password, $dbname) or die("unable to connect to database");



       $name="";
      if(isset($_POST['submit']))
          {
              $name = $_POST['nome'];
              $conn->query("insert into dati(nome) values('$name')");
          if(!$conn)
          { echo mysqli_error(); }
      else
      {
          echo "Successfully Inserted <br />";

      }
           }
?>
