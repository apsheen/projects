<?php
    // configuration
    require("../includes/config.php");

    $history = CS50::query("SELECT action, symbol, shares, price, time FROM history WHERE user_id = ?", $_SESSION["id"]);
    render("history.php", ["title" => "History", "history" => $history]);

?>