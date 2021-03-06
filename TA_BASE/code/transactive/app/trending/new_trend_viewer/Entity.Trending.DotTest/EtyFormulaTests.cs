using Dottest.Framework;
using Dottest.Framework.RecordState;
using Entity.Trending;
using NUnit.Framework;
using System;

namespace Entity.Trending.DotTest
{
    [TestFixture()]
    public class EtyFormulaTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/hGBvw", "+ulSKQ")]
        public void TestEtyFormula01()
        {
            EtyFormula etyFormula = new EtyFormula();

            string s = etyFormula.ConfigName;
            etyFormula.ConfigName = s;

            s = etyFormula.DPColor;
            etyFormula.DPColor = s;

            bool b = etyFormula.DPEnabled;
            etyFormula.DPEnabled = b;

            s = etyFormula.DPEquation;
            etyFormula.DPEquation = s;

            b = etyFormula.DPLblEnabled;
            etyFormula.DPLblEnabled = b;

            s = etyFormula.DPLblName;
            etyFormula.DPLblName = s;

            LineType lineType = etyFormula.DPType;
            etyFormula.DPType = lineType;

            ulong pkey = etyFormula.PKey;
            etyFormula.PKey = pkey;

        }

    }
}
