<table>
    <tr>
        <td style = "width: 400px" >Action</td>
        <td style = "width: 400px">Symbol</td>
        <td style = "width: 400px">Shares</td>
        <td style = "width: 400px">Price</td>
        <td style = "width: 400px">Time</td>
    </tr>

<?php foreach ($history as $history): ?>

    <tr>
        <td><?= $history["action"] ?></td>
        <td><?= $history["symbol"] ?></td>
        <td><?= $history["shares"] ?></td>
        <td>$<?= number_format($history["price"], 2) ?></td>
        <td>$<?= $history["time"] ?></td>
    </tr>

<?php endforeach ?>
</table>