package ui;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import logic.Fruit;
import logic.Game;
import logic.Kremlin;
import socket.Sala;
import socket.Sockets;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.net.Socket;
import java.net.URL;
import java.util.ResourceBundle;

public class MainWindowController implements Initializable {

    private ObservableList kremlinObservableList = FXCollections.observableArrayList();
    private ObservableList playerObservableList = FXCollections.observableArrayList();
    private ObservableList fruitObservableList = FXCollections.observableArrayList();
    private Game game = Game.getInstance();
    private Integer currentPlayer = 0;
    private Sockets socket = new Sockets();
    private String ip = "";
    private String playerType = "";

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        loadChoiceBoxes();
        beginGame1Button.setDisable(true);
        beginGame2Button.setDisable(true);
        acceptConection1Button.setDisable(true);
        acceptConection2Button.setDisable(true);
        refuseConection1Button.setDisable(true);
        refuseConection2Button.setDisable(true);
        createFruitButton.setDisable(true);
        createKremlinButton.setDisable(true);
        deleteFruitButton.setDisable(true);
        confirmPlayerButton.setDisable(true);
    }

    @FXML
    private Label ipLabel;

    @FXML
    private ChoiceBox<String> kremlinChoiceBox;

    @FXML
    private ChoiceBox<String> playerChoiceBox;

    @FXML
    private ChoiceBox<String> fruitChoiceBox;

    @FXML
    private Button createFruitButton;

    @FXML
    private Button deleteFruitButton;

    @FXML
    private Button createKremlinButton;

    @FXML
    private Button confirmPlayerButton;

    @FXML
    private Button searchConectionsButton;

    @FXML
    private Button acceptConection1Button;

    @FXML
    private Button refuseConection1Button;

    @FXML
    private Button acceptConection2Button;

    @FXML
    private Button refuseConection2Button;

    @FXML
    private Button beginGame1Button;

    @FXML
    private Button beginGame2Button;

    @FXML
    private TextField createKremlinIEntry;

    @FXML
    private TextField createKremlinJEntry;

    @FXML
    private TextField createFruitIEntry;

    @FXML
    private TextField createFruitJEntry;

    @FXML
    private TextField deleteFruitIEntry;

    @FXML
    private TextField deleteFruitJEntry;

    @FXML
    private TextField fruitPointsEntry;

    @FXML
    void acceptPlayer1(ActionEvent event) throws IOException {
        searchConectionsButton.setDisable(false);
        acceptConection1Button.setDisable(true);
        acceptConection2Button.setDisable(true);
        refuseConection1Button.setDisable(true);
        refuseConection2Button.setDisable(true);
        Sala sala = Sala.getInstance(1);
        System.out.println(playerType);
        System.out.println(playerType.length());
        if (playerType.startsWith("j") || !sala.ips[0].equals("")){
            sala.agregarJugador(ip);
            socket.enviar(ip, 8081, "si");
        }else{
            socket.enviar(ip, 8081, "no");
        }
    }

    @FXML
    void acceptPlayer2(ActionEvent event) throws IOException {
        searchConectionsButton.setDisable(false);
        acceptConection1Button.setDisable(true);
        acceptConection2Button.setDisable(true);
        refuseConection1Button.setDisable(true);
        refuseConection2Button.setDisable(true);
        Sala sala = Sala.getInstance(2);
        if (playerType.startsWith("j") || !sala.ips[0].equals("")){
            sala.agregarJugador(ip);
            socket.enviar(ip, 8081, "si");
        }else{
            socket.enviar(ip, 8081, "no");
        }
    }

    @FXML
    void refusePlayer(ActionEvent event) throws IOException {
        searchConectionsButton.setDisable(false);
        acceptConection1Button.setDisable(true);
        acceptConection2Button.setDisable(true);
        refuseConection1Button.setDisable(true);
        refuseConection2Button.setDisable(true);
        socket.enviar(ip, 8081, "no");
    }

    @FXML
    void beginPlayer1(ActionEvent event) throws IOException {
        Sala sala = Sala.getInstance(1);
        confirmPlayerButton.setDisable(false);
        for (int i = 0; i < sala.ips.length; i++){
            if (!sala.ips[i].equals("")){
                socket.enviar(sala.ips[i], 8081, "8082");
            }
        }
        acceptConection1Button.setDisable(true);
        refuseConection1Button.setDisable(true);
        beginGame1Button.setDisable(true);
        Thread thread = new Thread(sala);
        thread.start();
    }

    @FXML
    void beginPlayer2(ActionEvent event) throws IOException {
        Sala sala = Sala.getInstance(2);
        confirmPlayerButton.setDisable(false);
        for (int i = 0; i < sala.ips.length; i++){
            if (!sala.ips[i].equals("")){
                socket.enviar(sala.ips[i], 8081, "8083");
            }
        }
        acceptConection2Button.setDisable(true);
        refuseConection2Button.setDisable(true);
        beginGame2Button.setDisable(true);
        Thread thread = new Thread(sala);
        thread.start();
    }

    @FXML
    void searchConections(ActionEvent event) {
        searchConectionsButton.setDisable(true);
        ip = socket.escuchar(8081);
        playerType = socket.escuchar(8081);
        ipLabel.setText(ip);
        System.out.println(playerType);
        beginGame1Button.setDisable(false);
        beginGame2Button.setDisable(false);
        acceptConection1Button.setDisable(false);
        acceptConection2Button.setDisable(false);
        refuseConection1Button.setDisable(false);
        refuseConection2Button.setDisable(false);
    }

    @FXML
    void createKremlin(ActionEvent event) throws IOException {
        String posI = createKremlinIEntry.getText();
        String posJ = createKremlinJEntry.getText();
        String kremlin = kremlinChoiceBox.getValue();
        if (kremlin == null || posI.equals("") || posJ.equals("") || currentPlayer == 0){
            System.out.println("Seleccione una opcion");
        }else{
            switch (kremlin){
                case "Kremlin Rojo":
                    Kremlin redKremlin = new Kremlin(Integer.valueOf(posI), Integer.valueOf(posJ), 21);
                    game.addEnemy(redKremlin, currentPlayer);
                    System.out.println("Rojo");
                    break;
                case "Kremlin Azul":
                    Kremlin blueKremlin = new Kremlin(Integer.valueOf(posI), Integer.valueOf(posJ), 22);
                    game.addEnemy(blueKremlin, currentPlayer);
                    System.out.println("Azul");
                    break;
            }
            createFruitIEntry.setText("");
            createFruitJEntry.setText("");
        }
    }

    @FXML
    void createFruit(ActionEvent event) throws IOException {
        String points = fruitPointsEntry.getText();
        String posI = createFruitIEntry.getText();
        String posJ = createFruitJEntry.getText();
        String type = fruitChoiceBox.getValue();
        if (points.equals("") || posI.equals("") || posJ.equals("") || type == null || currentPlayer == 0){
            System.out.println("Llene todo");
        }else{
            switch (type){
                case "Manzana":
                    Fruit apple = new Fruit(Integer.valueOf(posI), Integer.valueOf(posJ), Integer.valueOf(points), 31);
                    game.addFruit(apple, currentPlayer);
                    break;
                case "Banano":
                    Fruit banana = new Fruit(Integer.valueOf(posI), Integer.valueOf(posJ), Integer.valueOf(points), 32);
                    game.addFruit(banana, currentPlayer);
                    break;
                case "Mango":
                    Fruit mango = new Fruit(Integer.valueOf(posI), Integer.valueOf(posJ), Integer.valueOf(points), 33);
                    game.addFruit(mango, currentPlayer);
                    break;
            }
            fruitPointsEntry.setText("");
            createFruitIEntry.setText("");
            createFruitJEntry.setText("");
        }
    }

    @FXML
    void deleteFruit(ActionEvent event) throws IOException {
        String posI = deleteFruitIEntry.getText();
        String posJ = deleteFruitJEntry.getText();
        if (posI.equals("") || posJ.equals("") || currentPlayer == 0){
            System.out.println("Llene todo");
        }else{
            Fruit fruit = new Fruit(Integer.valueOf(posI), Integer.valueOf(posJ), 0, 0);
            game.addFruit(fruit, currentPlayer);
            deleteFruitIEntry.setText("");
            deleteFruitJEntry.setText("");
        }
    }

    @FXML
    void confirmPlayer(ActionEvent event) {
        String player = playerChoiceBox.getValue();
        if (player == null){
            System.out.println("Seleccione una opcion");
        }else{
            createKremlinButton.setDisable(false);
            createFruitButton.setDisable(false);
            deleteFruitButton.setDisable(false);
            switch (player){
                case "Player 1":
                    currentPlayer = 1;
                    System.out.println(1);
                    break;
                case "Player 2":
                    currentPlayer = 2;
                    System.out.println(2);
                    break;
            }
        }
    }

    private void loadChoiceBoxes(){
        kremlinObservableList.removeAll(kremlinObservableList);
        String red = "Kremlin Rojo";
        String blue = "Kremlin Azul";
        kremlinObservableList.addAll(red, blue);
        kremlinChoiceBox.getItems().addAll(kremlinObservableList);

        playerObservableList.removeAll(playerObservableList);
        String p1 = "Player 1";
        String p2 = "Player 2";
        playerObservableList.addAll(p1, p2);
        playerChoiceBox.getItems().addAll(playerObservableList);

        fruitObservableList.removeAll(fruitObservableList);
        String apple = "Manzana";
        String banana = "Banano";
        String mango = "Mango";
        fruitObservableList.addAll(apple, banana, mango);
        fruitChoiceBox.getItems().addAll(fruitObservableList);
    }

}
