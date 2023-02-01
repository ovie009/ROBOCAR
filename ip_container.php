<?php
    include_once "./database_connect.php";
    $id = 1;
    // sql query
    $sql = "SELECT * FROM `ip` WHERE id = ?;";

    // create prepared statement
    $stmt = mysqli_stmt_init($connect);

    // run prepared statement
    if (!mysqli_stmt_prepare($stmt, $sql)) {
        // echo 'Query Failed';
    } else {
        // Bind parameters to the placeholder
        mysqli_stmt_bind_param($stmt, "s", $id);
        // run parameters inside database
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $ipAddress = $row['address'];
            $dateTime = $row['datetime'];
            $dateTime = strtotime($dateTime);
            $currentDateTime = date('Y-m-d G:i:s');
            $unixSeconds = date('U');
            $timeElapsed = $unixSeconds - $dateTime;

            ?> <label for="ip_address">Camserver Ip address:</label>
            <input type="text" name="ip_address" id="ip_address" value="<?php echo $ipAddress  ?>" placeholder="ip address of camserver" readonly>
            <button class="esp_now_submit" type="submit">submit</button> 
            <span  style="font-size: small;">Ip address last updated <?php echo formatTime($timeElapsed); ?></span><?php
        }
    }

    function formatTime($time) {
        if ($time == 0) { // if time is equal to zero
            return 'just now';
        } else if($time < 60) { // if time is less than 1 minute
            return $time." second".grammarCheck($time); 
        
        } else if($time < 3600) { // if time is less than 1 hour
            $timeInMinutes = floor($time / 60);
            return $timeInMinutes." minute".grammarCheck($timeInMinutes);
        
        } else if($time < 86400) { // if time is less than 1 day
            $timeInHours = floor($time / 3600);
            return $timeInHours." hour".grammarCheck($timeInHours);

        } else if($time < 2592000) { // if time is less than 1 day
            $timeInDays = floor($time / 86400);
            return $timeInDays." day".grammarCheck($timeInDays);
        } else {
            return 'more than a month ago';
        }
    }

    function grammarCheck($number) {
        if ($number == 1) {
            return ' ago';
        } else {
            return 's ago';
        }
        
    }
?>
