//
// Applet file generated automatically 
// time: Mon Nov 16 09:07:49 1998
// DX version: 3.1.2 (format), 4.1.1 (DXBeta)
//
// Java version 1.0
//
import dx.net.*;
import dx.runtime.*;
import java.util.*;
import java.awt.*;

public class optval extends DXLinkApplication {

    public void readNetwork() {


        SequencerNode Sequencer_1 = new SequencerNode (this.network, "Sequencer", 1, "Sequencer");
        this.network.addElement((Object)Sequencer_1);
        Sequencer_1.setInputValueString(4, "1");
        Sequencer_1.setInputValueString(5, "300");
        Sequencer_1.setInputValueString(6, "10");


        PickNode Pick_1 = new PickNode (this.network, "Pick", 1, "Pick_1");
        this.network.addElement((Object)Pick_1);


        WebOptionsNode WebOptions_2 = new WebOptionsNode (this.network, "WebOptions", 2, "WebOptions");
        this.network.addElement((Object)WebOptions_2);


        ImageNode Image_1 = new ImageNode (this.network, "Image", 1, "Image");
        this.network.addElement((Object)Image_1);
        Image_1.setInputValueString(5, "[49 39.75 21.6913]");
        Image_1.setInputValueString(6, "[59.1522 198.009 112.2]");
        Image_1.setInputValueString(10, "[0.0109428 -0.496945 0.867713]");
        Image_1.setInputValueString(11, "30.0");
        Image_1.setInputValueString(41, "pick");
        Image_1.setInputValueString(42, "Value");
        Image_1.addInputArc (49, WebOptions_2, 1);
    }
}
