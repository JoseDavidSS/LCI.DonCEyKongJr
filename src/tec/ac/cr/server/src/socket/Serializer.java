package socket;

import com.fasterxml.jackson.databind.ObjectMapper;
import logic.Fruit;
import logic.Kremlin;

import java.io.IOException;

public class Serializer {

    /**
     * Serializa un kremlin
     * @param kremlin
     * @return
     * @throws IOException
     */
    public static String serializeKremlin(Kremlin kremlin) throws IOException {
        ObjectMapper kremlinMapper = new ObjectMapper();
        return kremlinMapper.writeValueAsString(kremlin);

    }

    /**
     * Serializa un kremlin
     * @param fruit
     * @return
     * @throws IOException
     */
    public static String serializeFruit(Fruit fruit) throws IOException{
        ObjectMapper fruit_Mapper = new ObjectMapper();
        return fruit_Mapper.writeValueAsString(fruit);
    }

}
