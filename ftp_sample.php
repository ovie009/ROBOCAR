<?php

    // Connect to the FTP server
    $ftp_server = "ftp.example.com";
    $ftp_username = "username";
    $ftp_userpass = "password";

    // Connect to the FTP server
    // $ftp_server = "files.000webhost.com";
    // $ftp_username = "robotcar";
    // $ftp_userpass = "Robotcar@2022";

    $conn_id = ftp_connect($ftp_server) or die("Couldn't connect to $ftp_server");

    // Login to the FTP server
    $login_result = ftp_login($conn_id, $ftp_username, $ftp_userpass);

    // Check if login was successful
    if ((!$conn_id) || (!$login_result)) {
    echo "FTP connection has failed!";
    echo "Attempted to connect to $ftp_server for user $ftp_username";
    exit;
    } else {
    echo "Connected to $ftp_server, for user $ftp_username";
    }

    // Upload the file
    $local_file = "local_file.txt";
    $server_file = "server_file.txt";

    if (ftp_put($conn_id, $server_file, $local_file, FTP_ASCII)) {
    echo "Successfully uploaded $local_file to $server_file.";
    } else {
    echo "There was a problem.";
    }

    // Download the file
    $local_file = "local_file.txt";
    $server_file = "server_file.txt";

    // Create the directory
    $dir = "new_directory";

    if (ftp_mkdir($conn_id, $dir)) {
    echo "Successfully created $dir.";
    } else {
    echo "There was a problem creating $dir.";
    }

    
    // Delete the file
    $file = "server_file.txt";

    if (ftp_delete($conn_id, $file)) {
    echo "Successfully deleted $file.";
    } else {
    echo "There was a problem deleting $file.";
    }

    if (ftp_get($conn_id, $local_file, $server_file, FTP_ASCII)) {
    echo "Successfully written to $local_file.";
    } else {
    echo "There was a problem.";
    }

    // Close the FTP connection
    ftp_close($conn_id);

?>
