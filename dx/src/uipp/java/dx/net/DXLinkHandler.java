//

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/DXLinkHandler.java,v 1.2 1999/05/25 22:12:14 gda Exp $
 */
package dx.net;

public interface DXLinkHandler {
    public void outputHandler(String key, String msg, Object data);
    public boolean hasHandler(String key);
};

