using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ImageDefinition : NodeDefinition
    {
        private Cacheability defaultInternalCacheability;

        protected override CDBAllocator getCDBAllocator()
        {
            return ImageCDB.AllocateConfigurationDialog;
        }

        protected override Node newNode(Network net, int instance)
        {
            ImageNode d = new ImageNode(this, net, instance);
            return d;
        }

        public Cacheability DefaultInternalCacheability
        {
            get
            {
                return defaultInternalCacheability;
            }
        }

        public ImageDefinition()
        {
            defaultInternalCacheability = Cacheability.InternalsFullyCached;
        }

        public new static NodeDefinition AllocateDefinition()
        {
            return new ImageDefinition();
        }

        public override void finishDefinition()
        { }

        public override bool IsAllowedInMacro()
        {
            return false;
        }
    }
}
