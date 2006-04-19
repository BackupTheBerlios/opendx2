using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX
{
    using NUnit.Framework;

    [TestFixture]
    public class UIComponentTest
    {
        public UIComponentTest() { }

        [Test]
        public void ParseGeom()
        {
            int xp = 0, yp = 0, xs = 0, ys = 0;
            WinDX.UI.Utils.ParseGeometryComment("window: position = (0.25, .178), size = .88x.76, screen = 0",
                null, 1, ref xp, ref yp, ref xs, ref ys, null);

            Console.WriteLine("ParseGeometryComment Return: {0}, {1}, {2}, {3}", xp, yp, xs, ys);
            Assert.AreEqual(xp, 320);
            Assert.AreEqual(yp, 182);
            Assert.AreEqual(xs, 1126);
            Assert.AreEqual(ys, 778);
        }
    }
}
