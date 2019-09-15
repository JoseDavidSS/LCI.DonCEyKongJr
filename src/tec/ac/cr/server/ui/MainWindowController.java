package tec.ac.cr.server.ui;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextField;

import java.net.URL;
import java.util.ResourceBundle;

public class MainWindowController implements Initializable {
    private ObservableList kremlinObservableList = FXCollections.observableArrayList();
    private ObservableList playerObservableList = FXCollections.observableArrayList();
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
        String kremlin = kremlinChoiceBox.getValue();
        if (kremlin == null){
            System.out.println("Seleccione una opcion");
        }else{
            switch (kremlin){
                case "Kremlin Rojo":
                    System.out.println("Rojo");
                    break;
                case "Kremlin Azul":
                    System.out.println("Azul");
                    break;
            }
        }
    }

    @FXML
    void createFruit(ActionEvent event) {
        String points = fruitPointsEntry.getText();
        String posI = createFruitIEntry.getText();
        String posJ = createFruitJEntry.getText();
        if (points.equals("") || posI.equals("") || posJ.equals("")){
            System.out.println("Llene todo");
        }else{
            fruitPointsEntry.setText("");
            createFruitIEntry.setText("");
            createFruitJEntry.setText("");
        }
    }

    @FXML
    void deleteFruit(ActionEvent event) {
        String posI = deleteFruitIEntry.getText();
        String posJ = deleteFruitJEntry.getText();
        if (posI.equals("") || posJ.equals("")){
            System.out.println("Llene todo");
        }else{
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
    }

}
