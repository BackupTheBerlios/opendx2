//
// Applet file generated automatically 
// time: Tue Nov 24 15:52:12 1998
// DX version: 3.1.2 (format), 4.1.1 (DXBeta)
//
// Java version 1.0
//
import dx.net.*;
import dx.runtime.*;
import java.util.*;
import java.awt.*;

public class npvcall extends DXLinkApplication {

    public void readNetwork() {
        ControlPanel cp_2 = new ControlPanel(this.network, "Selection", 2);
        this.network.addPanel(cp_2);



        ToggleNode Toggle_1 = new ToggleNode (this.network, "Toggle", 1, "Toggle");
        this.network.addElement((Object)Toggle_1);

        Toggle toggle_Toggle_1 = new Toggle();
        Toggle_1.addInteractor(toggle_Toggle_1);
        toggle_Toggle_1.setStyle(0);
        toggle_Toggle_1.setLabelLines(1);
        toggle_Toggle_1.setLabel("Show Call");
        toggle_Toggle_1.setHorizontal();
        Toggle_1.reshape (toggle_Toggle_1, 0,0,153,32);
        toggle_Toggle_1.setOutputType(BinaryInstance.INTEGER);
        cp_2.addInteractor(toggle_Toggle_1);
        Vector Toggle_1_vn = new Vector(2);
        Vector Toggle_1_vo = new Vector(2);
        Toggle_1_vn.addElement("set_value");
        Toggle_1_vo.addElement("1");
        Toggle_1_vn.addElement("set_value");
        Toggle_1_vo.addElement("0");
        Toggle_1.setValues(Toggle_1_vn, Toggle_1_vo);
        Toggle_1.selectOption(1);


        ToggleNode Toggle_2 = new ToggleNode (this.network, "Toggle", 2, "Toggle");
        this.network.addElement((Object)Toggle_2);

        Toggle toggle_Toggle_2 = new Toggle();
        Toggle_2.addInteractor(toggle_Toggle_2);
        toggle_Toggle_2.setStyle(0);
        toggle_Toggle_2.setLabelLines(1);
        toggle_Toggle_2.setLabel("Show Put");
        toggle_Toggle_2.setHorizontal();
        Toggle_2.reshape (toggle_Toggle_2, 0,37,153,32);
        toggle_Toggle_2.setOutputType(BinaryInstance.INTEGER);
        cp_2.addInteractor(toggle_Toggle_2);
        Vector Toggle_2_vn = new Vector(2);
        Vector Toggle_2_vo = new Vector(2);
        Toggle_2_vn.addElement("set_value");
        Toggle_2_vo.addElement("1");
        Toggle_2_vn.addElement("set_value");
        Toggle_2_vo.addElement("0");
        Toggle_2.setValues(Toggle_2_vn, Toggle_2_vo);
        Toggle_2.selectOption(1);


        ToggleNode Toggle_3 = new ToggleNode (this.network, "Toggle", 3, "Toggle");
        this.network.addElement((Object)Toggle_3);

        Toggle toggle_Toggle_3 = new Toggle();
        Toggle_3.addInteractor(toggle_Toggle_3);
        toggle_Toggle_3.setStyle(0);
        toggle_Toggle_3.setLabelLines(1);
        toggle_Toggle_3.setLabel("Show Portfolio");
        toggle_Toggle_3.setHorizontal();
        Toggle_3.reshape (toggle_Toggle_3, 0,77,153,32);
        toggle_Toggle_3.setOutputType(BinaryInstance.INTEGER);
        cp_2.addInteractor(toggle_Toggle_3);
        Vector Toggle_3_vn = new Vector(2);
        Vector Toggle_3_vo = new Vector(2);
        Toggle_3_vn.addElement("set_value");
        Toggle_3_vo.addElement("1");
        Toggle_3_vn.addElement("set_value");
        Toggle_3_vo.addElement("0");
        Toggle_3.setValues(Toggle_3_vn, Toggle_3_vo);


        WebOptionsNode WebOptions_1 = new WebOptionsNode (this.network, "WebOptions", 1, "WebOptions");
        this.network.addElement((Object)WebOptions_1);


        ImageNode Image_3 = new ImageNode (this.network, "Image", 3, "Image");
        this.network.addElement((Object)Image_3);
        Image_3.setInputValueString(5, "[39.8125 14.8155 10.2725]");
        Image_3.setInputValueString(6, "[53.1545 -65.8721 45.8955]");
        Image_3.setInputValueString(10, "[-0.0713902 0.392949 0.916785]");
        Image_3.setInputValueString(11, "30.0");
        Image_3.setInputValueString(41, "camera");
        Image_3.setInputValueString(42, "Portfolio");
        Image_3.addInputArc (49, WebOptions_1, 1);
    }
}
