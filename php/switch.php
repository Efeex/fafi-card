<?php

  include ("connect.php");




  $uid = '';
  $bool;

  function uidBack() {
     // Check if we have parameters w1 and w2 being passed to the script through the URL
     if (isset($_GET["uid"])) {
        // Put the two words together with a space in the middle to form "hello world"
        $uid_js = $_GET["uid"];
        // Print out some JavaScript with $hello stuck in there which will put "hello world" into the javascript.
     //echo "<script language='text/javascript'>function sayHiFromPHP() { alert('Just wanted to say $hello!'); }</script>";
     }
     return $uid_js;
    }

    $sql = "SELECT uid FROM dati";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
      // output data of each row
      while($row = $result->fetch_assoc()) {
        $uid = uidBack();
          if ($row["uid"] == $uid) {
            echo('sisi');
            $bool = TRUE;
            //header("Location: read.php");
          } else {
            echo('nono');
            //header("Location: ../form.html");
          }
      }
    } else {
        echo "0 results";
    }

    if($bool == TRUE){

      # define the variables array
      $data = ['uid_log' => $uid ];

      # create the query string
      $query_string = http_build_query($data);

      header("Location: read.php" . (FALSE === empty($query_string) ? '?'.$query_string:''));
    } else{
      header("Location: ../form.html");
    }
?>
