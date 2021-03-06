using Dottest.Framework;
using NUnit.Framework;
using OPCTrendLib.OPCDataInterface;

namespace DotTest.Factories.OPCTrendLib.OPCDataInterface
{
    [TestFixture(), ObjectFactoryType()]
    public class OPCITEMDEFinternFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/tAeeg", "/u7rrQ")]
        internal static OPCITEMDEFintern CreateOPCITEMDEFintern01()
        {
            OPCITEMDEFintern oPCITEMDEFintern = new OPCITEMDEFintern();
            return oPCITEMDEFintern;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateOPCITEMDEFintern01()
        {
            OPCITEMDEFintern oPCITEMDEFintern = CreateOPCITEMDEFintern01();
            Assert.IsNotNull(oPCITEMDEFintern);
        }

    }
}
