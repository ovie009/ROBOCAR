
<?php
    // echo 'files: ';
    // print_r($_FILES);
    // echo 'Post: ';
    // print_r($_POST);
    
    // // Use the file_get_contents function to get the contents of the image
    $image = file_get_contents('php://input');
    $fileToWrite = "./image/image.jpg";
    file_put_contents($fileToWrite, $image);
    echo 'saved image';

?>
