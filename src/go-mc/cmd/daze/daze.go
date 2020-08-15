package main

import (
	"bytes"
	"github.com/Tnze/go-mc/yggdrasil"
	"log"

	"github.com/Tnze/go-mc/bot"
	"github.com/Tnze/go-mc/chat"
	_ "github.com/Tnze/go-mc/data/lang/en-us"
	pk "github.com/Tnze/go-mc/net/packet"
)

func main() {
	c := bot.NewClient()

	ygg, err := yggdrasil.Authenticate("3033784236@qq.com", "MC.1006.")
	if err != nil {
		log.Fatal(err)
	}

	c.Auth.UUID, c.Auth.Name = ygg.SelectedProfile()
	c.AsTk = ygg.AccessToken()

	//Login
	err = c.JoinServer("localhost", 58981)
	if err != nil {
		log.Fatal(err)
	}
	log.Println("Login success")

	//Register event handlers
	c.Events.GameStart = onGameStart
	c.Events.ChatMsg = onChatMsg
	c.Events.Disconnect = onDisconnect
	c.Events.PluginMessage = onPluginMessage

	//JoinGame
	err = c.HandleGame()
	if err != nil {
		log.Fatal(err)
	}
}

func onGameStart() error {
	log.Println("Game start")
	return nil //if err isn't nil, HandleGame() will return it.
}

func onChatMsg(c chat.Message, pos byte, uuid string) error {
	log.Println("Chat:", c.ClearString()) // output chat message without any format code (like color or bold)
	return nil
}

func onDisconnect(c chat.Message) error {
	log.Println("Disconnect:", c)
	return nil
}

func onPluginMessage(channel string, data []byte) error {
	switch channel {
	case "minecraft:brand":
		var brand pk.String
		if err := brand.Decode(bytes.NewReader(data)); err != nil {
			return err
		}
		log.Println("Server brand is:", brand)

	default:
		log.Println("PluginMessage", channel, data)
	}
	return nil
}
