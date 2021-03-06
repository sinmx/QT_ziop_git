using Dottest.Framework;
using Dottest.Framework.RecordState;
using Entity.Trending;
using NUnit.Framework;
using System;

namespace Entity.Trending.DotTest
{
    [TestFixture()]
    public class EtyEntityTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/KGXJg", "/b0Dbw")]
        public void TestEtyEntity01()
        {
            EtyEntity etyEntity = new EtyEntity();

            string s = etyEntity.Description;
            etyEntity.Description = s;

            s = etyEntity.DisplayName;
            etyEntity.DisplayName = s;

            s = etyEntity.Name;
            etyEntity.Name = s;

            ulong pkey = etyEntity.Pkey;
            etyEntity.Pkey = pkey;

            

        }

    }
}
