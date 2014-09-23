var datagramInterface = require('dgram');
var udpPort = 5000;

var udpServer = datagramInterface.createSocket('udp4');
udpServer.bind(udpPort);

var Map = require("collection").Map;
var clientMap = new Map();
var currentMessage;

var sendToAll = function (currentClient) 
{
    if (currentClient.value().LastMessageTime < Date.now() - 5000) 
    {
        console.log('Removing  IP: ' + currentClient.value().address + ':' + currentClient.value().port + '\n');
        clientMap.remove(currentClient);
    }
    else
    {
        udpServer.send(currentMessage, 0, currentMessage.length, currentClient.value().port, currentClient.value().address);
    }
}

udpServer.on('message', function (msg, sender) {
    //udpServer.send(msg, 0, msg.length, sender.port, sender.address);
    currentMessage = msg;
    if (!clientMap.has(sender.address + ':' + sender.port)) {
        console.log("New client at time " + Date.now() + " : " + sender.address + ':' + sender.port + '\n');
    }
    //console.log('From IP: ' + sender.address + ':' + sender.port + '\n' + msg);
    sender.lastMessageTime = Date.now();
    clientMap.set(sender.address + ':' + sender.port, sender);

    clientMap.each(sendToAll);
});