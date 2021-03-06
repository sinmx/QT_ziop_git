using Dottest.Framework;
using NUnit.Framework;
using STEE.ISCS.MulLanguage;
using TrendViewer;

namespace TrendViewer.DotTest
{
    [TestFixture()]
    public class LanguageHelperTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+3MJTw", "+gSXUA")]
        public void TestInitLanguageType01()
        {
            LanguageType langType = LanguageType.English;
            LanguageHelper.InitLanguageType(langType);
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+0noJQ", "/Fv0bQ")]
        public void TestInitAllStrings01()
        {
            LanguageHelper.InitAllStrings();
        }

        [Test]
        public void TestInitAllStrings02()
        {
            LanguageHelper.InitAllStrings();
        }
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+713cg", "+r8Afg")]
        public void TestLanguageHelperConstructor01()
        {
            LanguageHelper languageHelper = new LanguageHelper();
        }

    }
}
