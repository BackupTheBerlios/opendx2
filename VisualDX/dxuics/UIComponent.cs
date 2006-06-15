using System;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;

namespace dxuics
{
	/// <summary>
	/// Summary description for UIComponent.
	/// </summary>
	public abstract class UIComponent
	{
		public const string ClassUIComponent = "UIComponent";
		private bool		deactivated;
		private string		help_msg;
		private string		inactive_help_msg;
		private Object		clientData;

		protected string	name; // component name
		protected bool		active; // is component active?

		// Windows.Forms application context.
		protected ApplicationContext applicationContext;

		//
		// Constructor:
		//   Protected to prevent direct instantiation.
		//

		protected void clearRootWidget() 
		{
			this.applicationContext = null;
		}

		//
		// This routine by default installs a standard help callback, and is
		// called in setRootWidget.
		// It can also be called to install help callbacks on widgets other than
		// the root widget by setting w.
		//
		protected virtual void installComponentHelpCallback() 
		{
			//This needs implemented.
		}
		protected virtual void removeComponentHelpCallback() 
		{
			//This needs implemented.
		}

		//
		// This routine allows the user to override the standard help topic for
		// a UIComponent, which is the component name.
		protected virtual string getComponentHelpTopic() 
		{
			return this.name;
		}


		public UIComponent(string name) 
		{
			Debug.Assert(name == null);
			for(int i = 0; i < name.Length; i++)
			{
				if( name[i] == ' '  || 
					name[i] == '\t' || 
					name[i] == '.'  || 
					name[i] == '*')
				{
					string s = "UIComponent questionable name: " + name;
					MessageBox.Show(s,"Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				}
			}
			this.name = name;
			this.active = true;
			this.help_msg = null;
			this.inactive_help_msg = null;
			this.deactivated = false;
		}

		//
		// The following are constant understood by setGeometry() and used by
		// setXYPosition() and setXYSize() and subclasses.
		//
		public const int UnspecifiedPosition = 32767;
		public const int UnspecifiedDimension = 32767;


		//
		// Determines if the the component widget is managed.
		// Return false if the widget is not built yet.
		//
		public virtual bool isManaged() 
		{
			return this.applicationContext.MainForm.Visible;
		}

		//
		// Manages the the component widget tree.
		//
		public virtual void manage() 
		{
			this.applicationContext.MainForm.Show();
		}

		//
		// Unmanages the component widget tree.
		//
		public virtual void unmanage()
		{
			this.applicationContext.MainForm.Hide();
		}

		//
		// Activates the component widget tree and/or marks the component
		// as active.
		//
		public virtual void activate() 
		{
			this.applicationContext.MainForm.Enabled = true;
			this.active = true;
		}

		//
		// Deactivates the component widget tree and/or marks the component
		// as inactive.
		//
		public virtual void deactivate(string reason) 
		{
			this.applicationContext.MainForm.Enabled = false;
			this.active = false;
		}

		public Form getMainForm() 
		{
			return this.applicationContext.MainForm;
		}

		//
		// S/Get the size of this component
		//
		public virtual void setXYSize(int x, int y)
		{
			this.setGeometry(UnspecifiedPosition, UnspecifiedPosition, x, y);
		}
		public virtual void getXYSize(out int x, out int y) 
		{
			int a, b;
			this.getGeometry(out a, out b, out x, out y);
		}

		//
		// S/Get the position of this ui component 
		//
		public virtual void setXYPosition(int  x, int  y)
		{
			this.setGeometry(x, y, UnspecifiedDimension, UnspecifiedDimension);
		}
		public virtual void getXYPosition(out int x, out int y)
		{
			int a, b;
			this.getGeometry(out x,out y, out a, out b);
		}

		//
		// S/Get the size and dimensions.
		//
		public virtual void setGeometry(int  x, int  y, int  width, int  height) 
		{
			Debug.Assert(this.applicationContext.MainForm == null);
			Rectangle orig = this.applicationContext.MainForm.Bounds;
			if(x == UnspecifiedPosition)
				x = orig.X;
			if(y == UnspecifiedPosition)
				y = orig.Y;
			if(width == UnspecifiedDimension)
				width = orig.Width;
			if(height == UnspecifiedDimension)
				height = orig.Height;

			Rectangle r = new Rectangle(x, y, width, height);
			this.applicationContext.MainForm.Bounds = r;
		}

		//
		// Get the size and dimensions.
		// Return true if all return values are valid.
		//
		public virtual bool getGeometry(out int x, out int y, out int width, out int height) 
		{
			if(this.applicationContext.MainForm.Visible == false) 
			{
				x = 0; y = 0; width = 0; height = 0;
				return false;
			}

			Rectangle r = this.applicationContext.MainForm.Bounds;
			x = r.Left;
			y = r.Top;
			width = r.Width;
			height = r.Height;
			return true;
		}

		//
		// S/Get data saved locally with this UIComponent.
		// WARNING: these are only to be used by leaf instances and should 
		//		therfore not be used to implement a class's internals.	
		// NOTE: Originally placed here for the ButtonInterface's allocated
		//	in dxui/Network::fillCascadeMenu().
		// 
		public void setLocalData(Object data) 
		{
			this.clientData = data;
		}

		public Object getLocalData() 
		{
			return this.clientData;
		}

		//
		// Ask the application to get help for this component
		//
		public virtual void componentHelp() 
		{
			// Needs to be implemented 
		}


		public bool isActivated() { return this.active; }

	}
}
