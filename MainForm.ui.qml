import QtQuick 2.6
import QtQuick.Controls 1.5

Rectangle {
    property alias mouseArea: mouseArea

    width: 800
    height: 600

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        TabView {
            id: tabView
            x: 0
            y: 0
            width: 800
            height: 440


            Tab {
                id: general
                visible: true
                asynchronous: false
                active: true
                z: 2
                source: "General.qml"
                title: "Общее"

                Flow {
                    x: 5
                    y: 5
                    visible: true
                    flow: Flow.TopToBottom

                    CheckBox {
                        id: checkBox3
                        text: qsTr("Разработка прототипа")
                        z: 1
                    }

                    CheckBox {
                        id: checkBox4
                        text: qsTr("Разработка дизайна")
                    }

                    CheckBox {
                        id: checkBox5
                        text: qsTr("Верстка сайта")
                    }

                    CheckBox {
                        id: checkBox6
                        text: qsTr("Адаптивная верстка сайта")
                    }

                    CheckBox {
                        id: checkBox7
                        text: qsTr("Интеграция верстки на CMS 1C-Bitrix")
                    }

                    CheckBox {
                        id: checkBox8
                        text: qsTr("Настройка и доработка интернет-магазина")
                    }

                    CheckBox {
                        id: checkBox9
                        text: qsTr("Настройка SMS-рассылки")
                    }

                    CheckBox {
                        id: checkBox10
                        text: qsTr("Интеграция с 1С")
                    }
                }
            }

            Tab {
                id: catalog
                visible: true
                active: false
                source: "Catalog.qml"
                title: "Каталог"

                Flow {
                    x: 5
                    y: 5
                    visible: true
                    layoutDirection: Qt.LeftToRight
                    flow: Flow.TopToBottom

                    Repeater {
                            model: database
                            CheckBox { text: "Data: " + modelData }
                        }

                    CheckBox {
                        id: checkBox
                        text: qsTr("Список разделов")
                    }

                    CheckBox {
                        id: checkBox1
                        text: qsTr("Список товаров")
                    }

                    CheckBox {
                        id: checkBox2
                        text: qsTr("Карточка товара")
                    }
                }
            }
        }
    }
}
