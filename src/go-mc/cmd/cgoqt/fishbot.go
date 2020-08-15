package main

import (
	"fmt"
	"log"
	"unsafe"

	"io/ioutil"
	"net"
	"net/http"

	"github.com/Tnze/go-mc/bot"
	"github.com/Tnze/go-mc/chat"
	"github.com/google/uuid"
	"strconv"
	"strings"
	"time"
)

//#include "cgo.h"
// #cgo LDFLAGS: -L./
import "C"

func main() {

}

const timeout = 45

var (
	watch   chan time.Time
	clients = make(map[string]*bot.Client)
)

////export cgo_chatMsg
//func CgoChatMsg(_key *C.char, _msg *C.char) {
//	_, ok := clients[C.GoString(_key)]
//	log.Println(ok, C.GoString(_msg), C.GoString(_key))
//
//	clients[C.GoString(_key)].Chat(C.GoString(_msg))
//}

//export CgoNewClient
func CgoNewClient(addr_, name_, uuid_, accessToken_, sessionURL_ *C.char) *C.char {
	str := C.GoString(addr_)
	strs := strings.Split(str, ":")
	addr := strs[0]
	port := 25565
	if len(strs) == 2 {
		port, _ = strconv.Atoi(strs[1])
	}

	c := bot.NewClient()
	accessToken := C.GoString(accessToken_)
	sessionURL := C.GoString(sessionURL_)
	c.Name = C.GoString(name_)
	if accessToken != "" {
		c.Auth.AsTk = accessToken
		c.Auth.UUID = C.GoString(uuid_)

		if sessionURL != "" {
			c.Auth.SessionURL = sessionURL
		}
	}

	//Login
	err := c.JoinServer(addr, port)
	if err != nil {
		return C.CString(err.Error())
	}
	clients[c.Address] = c
	log.Println("Login success")

	//Register event handlers
	c.Events.GameStart = onGameStart
	c.Events.ChatMsg = onChatMsg
	c.Events.Disconnect = onDisconnect
	c.Events.Die = onDeath
	//c.Events.SoundPlay = onSound

	//JoinGame
	err = c.HandleGame()
	if err != nil {
		return C.CString(err.Error())
	}

	return nil
}

type ServerStatus struct {
	Description chat.Message
	Players     struct {
		Max    int
		Online int
		Sample []struct {
			ID   uuid.UUID
			Name string
		}
	}
	Version struct {
		Name     string
		Protocol int
	}
	Favicon string
	Delay   int32
}

//export CgoPingServer
func CgoPingServer(addr_ *C.char) *C.MCServerStatus {
	str := C.GoString(addr_)

	str2 := strings.Split(str, ":")
	addr := str2[0]
	port := 25565
	if len(str2) == 2 {
		port, _ = strconv.Atoi(str2[1])
	}

	_, SRV, err := net.LookupSRV("minecraft", "tcp", addr)
	if err == nil && len(SRV) > 0 {
		addr = SRV[0].Target
		port = int(SRV[0].Port)
	}

	resp, delay, err := bot.PingAndListTimeout(addr, port, time.Second*5)
	if err != nil {
		fmt.Printf("ping and list server fail: %v", err)
		return C.NewMCServerStatusErr(C.CString(err.Error()))
	}

	return C.NewMCServerStatus(C.CString(string(resp)), C.int(delay.Milliseconds()))

	//var s ServerStatus
	//err = json.Unmarshal(resp, &s)
	//if err != nil {
	//	fmt.Print("unmarshal resp fail:", err)
	//	return C.CString("Json unmarshal resp fail")
	//}
	//
	//s.Delay = int32(delay.Nanoseconds() / 1e6)
	//data, err := json.Marshal(s)
	//if err != nil {
	//	fmt.Printf("json.marshal failed, err:", err)
	//	return C.CString("Json marshal fail ")
	//}

	//return C.CString(string(data))
}

//export CgoSendMsg
func CgoSendMsg(addr,msg *C.char)  {
	clients[C.GoString(addr)].Chat(C.GoString(msg))
}

//export CgoDisconnect
func CgoDisconnect(addr *C.char) {
	clients[C.GoString(addr)].Disconnect()
}

//export CgoRespawn
func CgoRespawn(addr *C.char) {
	clients[C.GoString(addr)].Respawn()
}

var (
	gameStartCallback  C.GameStartCallback
	chatMsgCallback    C.ChatMsgCallback
	disconnectCallback C.DisconnectCallback
)

//export CgoRegGameStartCallback
func CgoRegGameStartCallback(cb C.GameStartCallback) {
	gameStartCallback = cb
}

//export CgoRegChatMsgCallback
func CgoRegChatMsgCallback(cb C.ChatMsgCallback) {
	chatMsgCallback = cb
}

//export CgoRegDisconnectCallback
func CgoRegDisconnectCallback(cb C.DisconnectCallback) {
	disconnectCallback = cb
}

func onGameStart(addr_ string) error {
	log.Println("Game start")
	addr := C.CString(addr_)
	defer C.free(unsafe.Pointer(addr))
	C.GameStartEvent(gameStartCallback, addr)
	//	watch = make(chan time.Time)
	//	go watchDog()

	//return c.UseItem(0)
	return nil
}

//
//func onSound(name string, category int, x, y, z float64, volume, pitch float32) error {
//	//if name == "entity.fishing_bobber.splash" {
//	//	if err := c.UseItem(0); err != nil { //retrieve
//	//		return err
//	//	}
//	//	log.Println("gra~")
//	//	time.Sleep(time.Millisecond * 300)
//	//	if err := c.UseItem(0); err != nil { //throw
//	//		return err
//	//	}
//	//	watch <- time.Now()
//	//}
//	return nil
//}

func onChatMsg(addr_ string, c string, pos byte, sender string) error {
	addr := C.CString(addr_)
	defer C.free(unsafe.Pointer(addr))

	msg := C.CString(c)
	defer C.free(unsafe.Pointer(msg))
	C.ChatMsgEvent(chatMsgCallback, addr, msg)
	return nil
}

//
func onDisconnect(addr string, c chat.Message) error {
	log.Println("Disconnect:", c.ClearString())
	cAddr := C.CString(addr)
	defer C.free(unsafe.Pointer(cAddr))

	msg := C.CString(c.ClearString())
	defer C.free(unsafe.Pointer(msg))
	C.DisconnectEvent(disconnectCallback, cAddr, msg)

	return nil
}

func onDeath(addr_ string) error {
	log.Println("Died and Respawned")
	//addr := C.CString(addr_)
	//defer C.free(unsafe.Pointer(addr))
	//C.DeathEvent(addr)
	return nil
}

//func watchDog() {
//	to := time.NewTimer(time.Second * timeout)
//	for {
//		select {
//		case <-watch:
//		case <-to.C:
//			log.Println("rethrow")
//			if err := c.UseItem(0); err != nil {
//				panic(err)
//			}
//		}
//		to.Reset(time.Second * timeout)
//	}
//}

//export CgoHttpGet
func CgoHttpGet(url_ *C.char) *C.HttpResponse {
	url := string(C.GoString(url_))

	resp, err := http.Get(url)
	if err != nil {
		return C.NewResponseError(C.CString(err.Error()))
	}

	body, err := ioutil.ReadAll(resp.Body)
	defer resp.Body.Close()

	return C.NewHttpResponse(C.CBytes(body), C.int(len(body)), C.CString(resp.Status), C.int(resp.StatusCode))
}

var client = &http.Client{
	Timeout: 10 * time.Second,
}

//export CgoHttpPost
func CgoHttpPost(url_ *C.char, payload_ *C.char) *C.HttpResponse {
	payload := C.GoString(payload_)
	url := C.GoString(url_)

	request, err := http.NewRequest(
		http.MethodPost,
		url,
		strings.NewReader(payload))
	if err != nil {
	    return C.NewResponseError(C.CString(err.Error()))
	}

	request.Header.Set("User-agent", "go-mc")
	request.Header.Set("Connection", "keep-alive")
	request.Header.Set("Content-Type", "application/json")

	resp, err := client.Do(request)
	if err != nil {
		return C.NewResponseError(C.CString(err.Error()))
	}

	body, _ := ioutil.ReadAll(resp.Body)
	defer resp.Body.Close()

	return C.NewHttpResponse(C.CBytes(body), C.int(len(body)), C.CString(resp.Status), C.int(resp.StatusCode))
}
