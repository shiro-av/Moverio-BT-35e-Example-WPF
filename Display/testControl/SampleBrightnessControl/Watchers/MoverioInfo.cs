//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using System;
using System.Collections.Generic;

namespace testControl.Watchers
{
    internal class MoverioInfo : IEquatable<MoverioInfo>
    {
        public readonly MoverioType type;
        public readonly string portName;

        public MoverioInfo(MoverioType type, string portName)
        {
            this.type = type;
            this.portName = portName;
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as MoverioInfo);
        }

        public bool Equals(MoverioInfo other)
        {
            return other != null &&
                   type == other.type &&
                   portName == other.portName;
        }

        public override int GetHashCode()
        {
            var hashCode = -1604319942;
            hashCode = (hashCode * -1521134295) + type.GetHashCode();
            hashCode = (hashCode * -1521134295) + EqualityComparer<string>.Default.GetHashCode(portName);
            return hashCode;
        }

        public static bool operator ==(MoverioInfo left, MoverioInfo right)
        {
            return EqualityComparer<MoverioInfo>.Default.Equals(left, right);
        }

        public static bool operator !=(MoverioInfo left, MoverioInfo right)
        {
            return !(left == right);
        }
    }
}
