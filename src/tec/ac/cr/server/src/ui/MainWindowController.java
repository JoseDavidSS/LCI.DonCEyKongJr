package ui;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextField;
import logic.Fruit;
import logic.Game;
import logic.Kremlin;

import java.net.URL;
import java.util.ResourceBundle;

public class MainWindowController implements Initializable {

    private ObservableList kremlinObservableList = FXCollections.observableArrayList();
    private ObservableList playerObservableList = FXCollections.observableArrayList();
    private ObservableList fruitObservableList = FXCollections.observableArrayList();
    private Game game = Game.getInstance();
    private Integer currentPlayer = 0;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        loadChoiceBoxes();
    }

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
    private Button beginServerButton;

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
    void beginServer(ActionEvent event) {
        System.out.println("Server Iniciado");
        beginServerButton.setDisable(true);
    }

    @FXML
    void createKremlin(ActionEvent event) {
        String posI = createKremlinIEntry.getText();
        String posJ = createKremlinJEntry.getText();
        String kremlin = kremlinChoiceBox.getValue();
        if (kremlin == null || posI.equals("") || posJ.equals("") || currentPlayer == 0){
            System.out.println("Seleccione una opcion");
        }else{
            switch (kremlin){
                case "Kremlin Rojo":
                    Kremlin redKremlin = new Kremlin(Integer.getInteger(posI), Integer.getInteger(posJ), 21);
                    game.addEnemy(redKremlin, currentPlayer);
                    System.out.println("Rojo");
                    break;
                case "Kremlin Azul":
                    Kremlin blueKremlin = new Kremlin(Integer.getInteger(posI), Integer.getInteger(posJ), 22);
                    game.addEnemy(blueKremlin, currentPlayer);
                    System.out.println("Azul");
                    break;
            }
            createFruitIEntry.setText("");
            createFruitJEntry.setText("");
        }
    }

    @FXML
    void createFruit(ActionEvent event) {
        String points = fruitPointsEntry.getText();
        String posI = createFruitIEntry.getText();
        String posJ = createFruitJEntry.getText();
        String type = fruitChoiceBox.getValue();
        if (points.equals("") || posI.equals("") || posJ.equals("") || type == null || currentPlayer == 0){
            System.out.println("Llene todo");
        }else{
            switch (type){
                case "Manzana":
                    Fruit apple = new Fruit(Integer.getInteger(posI), Integer.getInteger(posJ), Integer.getInteger(points), 31);
                    game.addFruit(apple, currentPlayer);
                    break;
                case "Banano":
                    Fruit banana = new Fruit(Integer.getInteger(posI), Integer.getInteger(posJ), Integer.getInteger(points), 32);
                    game.addFruit(banana, currentPlayer);
                    break;
                case "Mango":
                    Fruit mango = new Fruit(Integer.getInteger(posI), Integer.getInteger(posJ), Integer.getInteger(points), 33);
                    game.addFruit(mango, currentPlayer);
                    break;
            }
            fruitPointsEntry.setText("");
            createFruitIEntry.setText("");
            createFruitJEntry.setText("");
        }
    }

    @FXML
    void deleteFruit(ActionEvent event) {
        String posI = deleteFruitIEntry.getText();
        String posJ = deleteFruitJEntry.getText();
        if (posI.equals("") || posJ.equals("") || currentPlayer == 0){
            System.out.println("Llene todo");
        }else{
            Fruit fruit = new Fruit(Integer.getInteger(posI), Integer.getInteger(posJ), 0, 31);
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
