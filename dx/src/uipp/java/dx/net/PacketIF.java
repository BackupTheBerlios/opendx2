//
package dx.net;

public interface PacketIF {
    public void setInputValue (int param, String value);
    public void setOutputValue (String value);
    public void setOutputValues (String name, String value);
    public void handleMessage (String msg);
};

