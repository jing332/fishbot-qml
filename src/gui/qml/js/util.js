.pragma library
.import "./global.js" as G

/*显示上下文菜单*/
var showContentMenu = function (items, parent) {
    G.appState.contentMenu.show(items)
}

var showLoadingDialog = function () {
    G.appState.loadingDlg.open()
}

var hideLoadingDialog = function () {
    if (G.appState.loadingDlg)
        G.appState.loadingDlg.close()
}

/*显示添加服务器对话框*/
var showAddServerDialog = function (cb) {
    var comp = Qt.createComponent("qrc:/qml/dialogs/AddServerDialog.qml")
    G.appState.addServerDlg = comp.createObject(G.appState.mainWindow, {})
    G.appState.addServerDlg.closed.connect(function () {
        G.appState.addServerDlg.destroy()
        G.appState.addServerDlg = null
    })
    G.appState.addServerDlg.finished.connect(function (name, addr) {
        cb(name, addr)
    })
    G.appState.addServerDlg.open()
}

/*显示编辑服务器对话框*/
var showEditServerDialog = function (name, addr, cb) {
    var comp = Qt.createComponent("qrc:/qml/dialogs/AddServerDialog.qml")
    G.appState.addServerDlg = comp.createObject(G.appState.mainWindow, {
                                                    "name": name,
                                                    "addr": addr
                                                })
    G.appState.addServerDlg.closed.connect(function () {
        G.appState.addServerDlg.destroy()
        G.appState.addServerDlg = null
    })
    G.appState.addServerDlg.finished.connect(function (name, addr) {
        cb(name, addr)
    })
    G.appState.addServerDlg.open()
}
/*显示添加账户对话框*/
var showAddAccountDialog = function (cb) {
    var comp = Qt.createComponent("qrc:/qml/dialogs/AddAccountDialog.qml")
    G.appState.addAccountDlg = comp.createObject(G.appState.mainWindow, {
                                                     "width": Qt.binding(
                                                                  function () {
                                                                      return G.appState.mainWindow.width
                                                                  }),
                                                     "height": Qt.binding(
                                                                   function () {
                                                                       return G.appState.mainWindow.height
                                                                   })
                                                 })
    G.appState.addAccountDlg.closed.connect(function () {
        G.appState.addAccountDlg.destroy()
        G.appState.addAccountDlg = null
    })
    G.appState.addAccountDlg.finished.connect(function (username, password) {
        if ("" !== password)
            showLoadingDialog()
        cb(username, password)
    })
    G.appState.addAccountDlg.open()
}
var setAddAccountDialogErrorText = function (text) {
    G.appState.addAccountDlg.errorText = text
}

var closeAddAccountDialog = function () {
    G.appState.addAccountDlg.close()
}
