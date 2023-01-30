
<?php
    include_once "./database_connect.php";


    $motion = 0;
    $data = "captured_image";
    $sql = "UPDATE `robocar_datastream` SET `data` = '".$data."', `datetime` = CURRENT_TIMESTAMP,`motion_detected` = '".$motion."' WHERE `robocar_datastream`.`id` = 1;";
    mysqli_query($connect, $sql);

    // // Use the file_get_contents function to get the contents of the image
    $image = file_get_contents('php://input');
    $fileToWrite = "IMAGE/image.jpg";
    file_put_contents($fileToWrite, $image);
    // echo 'saved image';
    // echo $image;
?>
