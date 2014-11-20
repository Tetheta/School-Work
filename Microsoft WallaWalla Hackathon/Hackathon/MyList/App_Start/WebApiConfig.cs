using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Http;
using System.Web.Http.Routing;

namespace MyList
{
    public static class WebApiConfig
    {
        public static void Register(HttpConfiguration config)
        {
            // Web API configuration and services

            // Web API routes
            config.MapHttpAttributeRoutes();

            //GetInvididualPosting
            config.Routes.MapHttpRoute(
                name: "GetIndividualListing",
                routeTemplate: "api/GetIndividualListing/{listingId}",
                defaults: new { controller = "Listings", listingId = RouteParameter.Optional }
            );

            //CustomerLogin
            config.Routes.MapHttpRoute(
                name: "GetValidateLogin",
                routeTemplate: "api/ValidateLogin/{email}/{passwd}",
                defaults: new { controller = "Listings", email = RouteParameter.Optional, passwd = RouteParameter.Optional }
            );

            //GetAllPostingsForCustomer
            config.Routes.MapHttpRoute(
                name: "GetListingsForCustomer",
                routeTemplate: "api/GetListingsForCustomer/{customerId}",
                defaults: new { controller = "Listings", customerId = RouteParameter.Optional }
            );

            //GetCategoryPostings
            config.Routes.MapHttpRoute(
                name: "GetCategoryListings",
                routeTemplate: "api/GetCategoryListings/{category}",
                defaults: new { controller = "Listings", category = RouteParameter.Optional }
            );

            config.Routes.MapHttpRoute(
                name: "GetTitleKeywordListings",
                routeTemplate: "api/GetTitleKeywordListings/{param1}",
                defaults: new { controller = "Listings", param1 = RouteParameter.Optional }
            );

            //GetCategoryPostings
            config.Routes.MapHttpRoute(
                name: "GetOther1KeywordListings",
                routeTemplate: "api/GetOther1KeywordListings/{keyword}",
                defaults: new { controller = "Listings", keyword = RouteParameter.Optional }
            );

            config.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}",
                defaults: new { id = RouteParameter.Optional }
            );

        }
    }
}
