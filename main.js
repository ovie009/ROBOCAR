$(document).ready(function() {

    $(".car-buttons").click(function() {

        let direction = this.id; // get the id of the button
        // the id of the button is equal to the direction of the button
        $.post("updateDb.php", {
            car: direction
        })

        console.log(this.id)
    })

    $(".reset-camera").click(function() {
        let direction = 'center'; 
        $.post("updateDb.php", {
            camera: direction
        })
    })

    $("#camera-left").click(function() {
        let direction = 'left'; 
        $.post("updateDb.php", {
            camera: direction
        })
    })

    $("#camera-right").click(function() {
        let direction = 'right'; 
        $.post("updateDb.php", {
            camera: direction
        })
    })

});