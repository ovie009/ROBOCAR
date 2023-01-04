
<?php
    include_once "./database_connect.php";

    // // Use the file_get_contents function to get the contents of the image
    $image = file_get_contents('php://input');
    $fileToWrite = "./image/image.jpg";
    file_put_contents($fileToWrite, $image);
    echo 'saved image';

    $motion = 0;
    $sql = "UPDATE `robocar_datastream` SET `motion_detected` = '".$motion."' WHERE `robocar_datastream`.`id` = 1;";
    mysqli_query($connect, $sql);
?>
